package ru.qwert21.labs.C5.display;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.geom.GeneralPath;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.io.File;
import java.io.IOException;

import static ru.qwert21.labs.C5.display.GraphicsDisplayStyle.*;

public class GraphicsDisplay extends JPanel {
	static private final int MARKER_RADIUS = 5;

	GraphicsData data = new GraphicsData();

	private GraphicsViewport viewport = new GraphicsViewport();
	private GraphicsViewport oldViewport;

	private double scaleX, scaleY;

	private boolean showAxes = true;
	private boolean showMarkers = true;
	private boolean showClosedAreas = true;
	private boolean doFlip = false;

	public GraphicsDisplay() {
		setBackground(Color.WHITE);

		this.setLayout(new BorderLayout());
		this.add(new GraphicsDisplayOptionPanel(this), BorderLayout.CENTER);
	}

	public void setShowAxes(boolean showAxes) {
		this.showAxes = showAxes;
	}

	public void setShowMarkers(boolean showMarkers) {
		this.showMarkers = showMarkers;
	}

	public void setShowClosedAreas(boolean showClosedAreas) {
		this.showClosedAreas = showClosedAreas;
	}

	public void setDoFlip(boolean doFlip) {
		this.doFlip = doFlip;
	}

	public boolean isShowAxes() {
		return showAxes;
	}

	public boolean isShowMarkers() {
		return showMarkers;
	}

	public boolean isShowClosedAreas() {
		return showClosedAreas;
	}

	public boolean isDoFlip() {
		return doFlip;
	}

	public void openFromFile(File file) throws IOException {
		data.openFromFile(file);
		viewport = data.defaultViewport.clone();
	}

	public void saveToFile(File file) throws IOException {
		data.saveToFile(file);
	}

	public void restoreRatio() {
		if (data.empty()) return;

		scaleX = getWidthProxy() / (viewport.maxX - viewport.minX);
		scaleY = getHeightProxy() / (viewport.maxY - viewport.minY);

		double scale = Math.min(scaleX, scaleY);

		double offsetX = (getWidthProxy() / scale - (viewport.maxX - viewport.minX)) / 2;
		double offsetY = (getHeightProxy() / scale - (viewport.maxY - viewport.minY)) / 2;

		updateViewport(new GraphicsViewport(
			viewport.minX - offsetX,
			viewport.maxX + offsetX,
			viewport.minY - offsetY,
		viewport.maxY + offsetY
		));
	}

	public void showAll() {
		updateViewport(data.defaultViewport.clone());
	}

	public void updateViewport(GraphicsViewport newViewport) {
		if (data.empty()) return;

		oldViewport = viewport;
		viewport = newViewport;

		repaint();
	}

	public void previousViewport() {
		if (oldViewport != null) {
			viewport = oldViewport;
			oldViewport = null;

			repaint();
		}
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		if (data.empty()) return;

		Graphics2D canvas = (Graphics2D) g;

		Stroke oldStroke = canvas.getStroke();
		Color oldColor = canvas.getColor();
		Font oldFont = canvas.getFont();
		AffineTransform oldTransform = canvas.getTransform();

		canvas.setFont(fontCommon);
		paintDisplay(canvas);

		canvas.setTransform(oldTransform);
		canvas.setFont(oldFont);
		canvas.setColor(oldColor);
		canvas.setStroke(oldStroke);
	}

	private void paintDisplay(Graphics2D canvas) {
		scaleX = getWidthProxy() / (viewport.maxX - viewport.minX);
		scaleY = getHeightProxy() / (viewport.maxY - viewport.minY);

		if (doFlip) {
			canvas.translate(getWidth() / 2., getHeight() / 2.);
			canvas.rotate(-Math.PI / 2);
			canvas.translate(-getWidthProxy() / 2., -getHeightProxy() / 2.);
		}

		if (showClosedAreas) {
			paintAreas(canvas);
		}

		if (showAxes) {
			paintAxes(canvas);
		}

		paintGraphics(canvas);

		if (showMarkers) {
			paintMarkers(canvas);
		}
	}

	private void paintGraphics(Graphics2D canvas) {
		GeneralPath path = new GeneralPath();

		for (int i = 0; i < data.points.length; i++) {
			Point ptCvs = dataToCanvas(data.points[i]);

			if (i == 0) {
				path.moveTo(ptCvs.x, ptCvs.y);
			} else {
				path.lineTo(ptCvs.x, ptCvs.y);
			}
		}

		canvas.setStroke(strokeGraphics);
		canvas.setColor(colorGraphics);

		canvas.draw(path);
	}

	private void paintMarker(Graphics2D canvas, int x, int y, boolean highlight) {
		if (highlight) {
			canvas.setColor(colorMarkersHighlighted);
		} else {
			canvas.setColor(colorMarkers);
		}

		canvas.drawLine(x - MARKER_RADIUS, y, x + MARKER_RADIUS, y);
		canvas.drawLine(x, y - MARKER_RADIUS, x, y + MARKER_RADIUS);
		canvas.drawLine(x - MARKER_RADIUS, y - MARKER_RADIUS, x + MARKER_RADIUS, y + MARKER_RADIUS);
		canvas.drawLine(x + MARKER_RADIUS, y - MARKER_RADIUS, x - MARKER_RADIUS, y + MARKER_RADIUS);
	}

	private void paintMarkers(Graphics2D canvas) {
		canvas.setStroke(strokeMarkers);
		canvas.setColor(colorMarkers);

		for (Point2D.Double pt : data.points) {
			Point ptCvs = dataToCanvas(pt);

			paintMarker(canvas, ptCvs.x, ptCvs.y, checkValue(pt.y));
		}
	}

	private void paintAxes(Graphics2D canvas) {
		canvas.setStroke(strokeAxes);
		canvas.setColor(colorAxes);

		Point pt = dataToCanvas(new Point2D.Double(0, 0));

		int width = getWidthProxy();
		int height = getHeightProxy();

		canvas.drawLine(0, pt.y, width - 2, pt.y);
		canvas.drawString("X", width - 10, pt.y - 10);

		canvas.drawLine(pt.x, 0, pt.x, height);
		canvas.drawString("Y", pt.x - 20, 10);

		canvas.setStroke(strokeArrows);

		GeneralPath arrow = new GeneralPath();
		arrow.moveTo(width - 10, pt.y - 4);
		arrow.lineTo(width - 2, pt.y);
		arrow.lineTo(width - 10, pt.y + 4);
		arrow.lineTo(width - 10, pt.y - 4);
		arrow.closePath();
		canvas.draw(arrow);
		canvas.fill(arrow);

		arrow = new GeneralPath();
		arrow.moveTo(pt.x - 4, 10);
		arrow.lineTo(pt.x, 2);
		arrow.lineTo(pt.x + 4, 10);
		arrow.lineTo(pt.x - 4, 10);
		arrow.closePath();
		canvas.draw(arrow);
		canvas.fill(arrow);
	}

	private void paintAreas(Graphics2D canvas) {
		for (GraphicsClosedArea area : data.areas) {
			GeneralPath path = new GeneralPath();

			Point ptFirst = dataToCanvas(new Point2D.Double(area.leftX, 0));
			path.moveTo(ptFirst.x, ptFirst.y);

			for (int i = area.leftInd; i <= area.rightInd; i++) {
				Point ptCvs = dataToCanvas(data.points[i]);

				path.lineTo(ptCvs.x, ptCvs.y);
			}

			Point ptLast = dataToCanvas(new Point2D.Double(area.rightX, 0));
			path.lineTo(ptLast.x, ptLast.y);

			path.closePath();

			canvas.setColor(colorAreas);
			canvas.fill(path);

			String str = String.format("%.04f", area.area);

			canvas.setColor(Color.BLACK);
			Rectangle2D rect = canvas.getFont().getStringBounds(str, canvas.getFontRenderContext());

			Point ptCenter = dataToCanvas(area.center);

			canvas.drawString(
				str,
				ptCenter.x - (int) rect.getWidth() / 2,
				ptCenter.y
			);
		}
	}

	Point dataToCanvas(Point2D.Double pt) {
		return new Point(
			(int) (scaleX * (pt.x - viewport.minX)),
			(int) (getHeightProxy() - scaleY * (pt.y - viewport.minY))
		);
	}

	Point2D.Double canvasToData(Point pt) {
		return new Point2D.Double(
			viewport.minX + pt.x / scaleX,
			viewport.minY - (pt.y - getHeightProxy()) / scaleY
		);
	}

	// if doFlip width and height swaps
	int getWidthProxy() {
		return doFlip ? getHeight() : getWidth();
	}

	int getHeightProxy() {
		return doFlip ? getWidth() : getHeight();
	}

	private boolean checkValue(double d) {
		int value = Math.abs((int) d);

		int prevDigit = 10;
		while (value != 0) {
			int curDigit = value % 10;

			if (curDigit >= prevDigit) {
				return false;
			}

			prevDigit = curDigit;
			value /= 10;
		}

		return true;
	}
}
