package ru.qwert21.labs.C4;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.GeneralPath;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.util.LinkedList;
import java.util.List;

public class GraphicsDisplay extends JPanel {
	static private final int MARKER_RADIUS = 5;

	private Point2D.Double[] data;
	private double minX, maxX, minY, maxY;
	private final List<GraphicsClosedArea> areas = new LinkedList<>();
	private double scaleX, scaleY, scale, offsetX, offsetY;

	private final Stroke strokeGraphics, strokeAxes, strokeArrows, strokeMarkers;
	private final Color colorGraphics, colorAxes, colorMarkers, colorMarkersHighlighted, colorAreas;

	private boolean showAxes = true;
	private boolean showMarkers = false;
	private boolean showClosedAreas = true;
	private boolean doFlip = false;
	private boolean doStretch = false;

	public GraphicsDisplay() {
		setBackground(Color.WHITE);

		strokeGraphics = new BasicStroke(2.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
			10.f, new float[]{8, 3, 2, 3, 2, 3, 4, 3, 4, 3}, 0.f);

		colorGraphics = new Color(0xdd4444);

		strokeAxes = new BasicStroke(2.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
			10.f, null, 0.f);

		strokeArrows = new BasicStroke(4.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
			10.f, null, 0.f);

		colorAxes = Color.BLACK;

		strokeMarkers = new BasicStroke(1.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
			10.f, null, 0.f);

		colorMarkers = colorGraphics;

		colorMarkersHighlighted = new Color(0x4444dd);

		colorAreas = new Color(0x66ff66);
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
	public void setDoStretch(boolean doStretch) {
		this.doStretch = doStretch;
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
	public boolean isDoStretch() {
		return doStretch;
	}

	public void setData(Point2D.Double[] data) {
		this.data = data.clone();

		minX = data[0].x;
		maxX = data[data.length - 1].x;
		minY = data[0].y;
		maxY = data[0].y;

		for (int i = 1; i < data.length; i++) {
			minY = Math.min(minY, data[i].y);
			maxY = Math.max(maxY, data[i].y);
		}

		findClosedAreas();
	}

	private void findClosedAreas() {
		areas.clear();

		boolean isStartArea = false;
		double curArea = 0;
		double nextLeftX = 0;
		int prevCtrl = 0;
		double maxY = 0;
		for (int i = 1; i < data.length; i++) {
			if (data[i].y * data[i - 1].y <= 0) {
				double ptX = data[i].x - Math.abs((data[i].y) / (data[i].y - data[i - 1].y) * (data[i].x - data[i - 1].x));

				if (isStartArea) {
					curArea += 0.5 * (ptX - data[i - 1].x) * (data[i - 1].y);

					if (prevCtrl != i - 1) {
						areas.add(new GraphicsClosedArea(
							prevCtrl, i - 1, curArea,
							nextLeftX, ptX, new Point2D.Double((ptX + nextLeftX) / 2, maxY / 2 * (data[prevCtrl].y < 0 ? -1 : 1))
						));
					}
				}

				isStartArea = true;
				curArea = 0.5 * (data[i].x - ptX) * (data[i].y);
				nextLeftX = ptX;
				prevCtrl = i;
				maxY = 0;
			} else {
				curArea += 0.5 * (data[i].x - data[i - 1].x) * (data[i].y + data[i - 1].y);
			}

			maxY = Math.max(Math.abs(maxY), Math.abs(data[i].y));
		}
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);

		if (data == null) return;

		Graphics2D canvas = (Graphics2D) g;

		Stroke oldStroke = canvas.getStroke();
		Color oldColor = canvas.getColor();

		paintDisplay(canvas);

		canvas.setColor(oldColor);
		canvas.setStroke(oldStroke);
	}

	private void paintDisplay(Graphics2D canvas) {
		scaleX = getWidthProxy() / (maxX - minX);
		scaleY = getHeightProxy() / (maxY - minY);

		scale = Math.min(scaleX, scaleY);

		offsetX = (maxX - minX) * (scaleX - scale) / 2;
		offsetY = (maxY - minY) * (scaleY - scale) / 2;

		if (doFlip) {
			canvas.translate(getWidth() / 2., getHeight() / 2.);
			canvas.rotate(-Math.PI / 2);
			canvas.translate(-getWidthProxy() / 2., -getHeightProxy() / 2.);
		}

		if (showClosedAreas) {
			paintAreas(canvas);
		}

		if (showAxes) {
			paintAxes(
				canvas,
				(int) (canvasX(0)),
				(int) (canvasY(0))
			);
		}

		paintGraphics(canvas);

		if (showMarkers) {
			paintMarkers(canvas);
		}
	}

	private void paintGraphics(Graphics2D canvas) {
		GeneralPath path = new GeneralPath();

		for (int i = 0; i < data.length; i++) {
			double x = canvasX(data[i].x);
			double y = canvasY(data[i].y);

			if (i == 0) {
				path.moveTo(x, y);
			} else {
				path.lineTo(x, y);
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

		for (Point2D.Double pt : data) {
			double x = canvasX(pt.x);
			double y = canvasY(pt.y);

			paintMarker(canvas, (int) x, (int) y, checkValue(pt.y));
		}
	}

	private void paintAxes(Graphics2D canvas, int x, int y) {
		canvas.setStroke(strokeAxes);
		canvas.setColor(colorAxes);

		int width = getWidthProxy();
		int height = getHeightProxy();

		canvas.drawLine(0, y, width - 2, y);
		canvas.drawString("X", width - 10, y - 10);

		canvas.drawLine(x, 0, x, height);
		canvas.drawString("Y", x - 20, 10);

		canvas.setStroke(strokeArrows);

		GeneralPath arrow = new GeneralPath();
		arrow.moveTo(width - 10, y - 4);
		arrow.lineTo(width - 2, y);
		arrow.lineTo(width - 10, y + 4);
		arrow.lineTo(width - 10, y - 4);
		arrow.closePath();
		canvas.draw(arrow);
		canvas.fill(arrow);

		arrow = new GeneralPath();
		arrow.moveTo(x - 4, 10);
		arrow.lineTo(x, 2);
		arrow.lineTo(x + 4, 10);
		arrow.lineTo(x - 4, 10);
		arrow.closePath();
		canvas.draw(arrow);
		canvas.fill(arrow);
	}

	private void paintAreas(Graphics2D canvas) {
		for (GraphicsClosedArea area : areas) {
			GeneralPath path = new GeneralPath();
			path.moveTo(canvasX(area.leftX), canvasY(0));

			for (int i = area.leftInd; i <= area.rightInd; i++) {
				path.lineTo(canvasX(data[i].x), canvasY(data[i].y));
			}

			path.lineTo(canvasX(area.rightX), canvasY(0));

			path.closePath();

			canvas.setColor(colorAreas);
			canvas.fill(path);

			String str = String.format("%.04f", area.area);

			canvas.setColor(Color.BLACK);
			Rectangle2D rect = canvas.getFont().getStringBounds(str, canvas.getFontRenderContext());
			canvas.drawString(
				str,
				(int) (canvasX(area.center.x) - rect.getWidth() / 2),
				(int) canvasY(area.center.y)
			);
		}
	}

	private double canvasX(double x) {
		if (doStretch) {
			return scaleX * (x - minX);
		} else {
			return offsetX + scale * (x - minX);
		}
	}

	private double canvasY(double y) {
		if (doStretch) {
			return getHeightProxy() - scaleY * (y - minY);
		} else {
			return getHeightProxy() - offsetY - scale * (y - minY);
		}
	}

	// if doFlip width and height swaps
	private int getWidthProxy() {
		return doFlip ? getHeight() : getWidth();
	}

	private int getHeightProxy() {
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
