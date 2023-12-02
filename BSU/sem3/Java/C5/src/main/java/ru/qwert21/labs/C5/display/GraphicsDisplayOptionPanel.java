package ru.qwert21.labs.C5.display;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

import static ru.qwert21.labs.C5.display.GraphicsDisplayStyle.*;

class GraphicsDisplayOptionPanel extends JPanel implements MouseMotionListener, MouseListener {
	static private final int POINT_SELECTION_RADIUS = 20;
	static private final int POINT_LABEL_OFFSET = 6;

	private final GraphicsDisplay display;

	private int selectedPointInd = -1;

	private boolean isMouseDown = false;

	private Point viewportCornerA, viewportCornerB;

	public GraphicsDisplayOptionPanel(GraphicsDisplay display) {
		this.display = display;

		this.setOpaque(false);
		this.addMouseListener(this);
		this.addMouseMotionListener(this);
	}

	@Override
	protected void paintComponent(Graphics g) {
		Graphics2D canvas = (Graphics2D) g;

		AffineTransform oldTransform = canvas.getTransform();

		if (display.isDoFlip()) {
			canvas.translate(getWidth() / 2., getHeight() / 2.);
			canvas.rotate(-Math.PI / 2);
			canvas.translate(-display.getWidthProxy() / 2., -display.getHeightProxy() / 2.);
		}

		if (selectedPointInd != -1) {
			paintSelectedPoint(canvas);
		}

		canvas.setTransform(oldTransform);

		paintSelectingViewport(canvas);
	}

	private void paintSelectedPoint(Graphics2D canvas) {
		Point2D.Double pt = display.data.points[selectedPointInd];

		Point ptCvs = display.dataToCanvas(pt);

		canvas.setStroke(strokeAxes);
		canvas.setColor(colorGraphics);

		canvas.drawOval(ptCvs.x - 6, ptCvs.y - 6, 13, 13);

		canvas.setFont(fontCommon);
		canvas.setColor(Color.BLACK);

		String str = String.format("(%.04f; %.04f)", pt.x, pt.y);
		Rectangle2D rect = fontCommon.getStringBounds(str, canvas.getFontRenderContext());

		int labelX, labelY;

		if (ptCvs.x + rect.getWidth() > display.getWidthProxy()) {
			labelX = ptCvs.x - (int) rect.getWidth() - POINT_LABEL_OFFSET;
		} else {
			labelX = ptCvs.x + POINT_LABEL_OFFSET;
		}

		if (ptCvs.y - rect.getHeight() < 0) {
			labelY = ptCvs.y + (int) rect.getHeight() + POINT_LABEL_OFFSET;
		} else {
			labelY = ptCvs.y - POINT_LABEL_OFFSET;
		}

		canvas.drawString(str, labelX, labelY);
	}

	private void paintSelectingViewport(Graphics2D canvas) {
		if (viewportCornerA == null) return;

		canvas.setStroke(strokeSelecting);
		canvas.setColor(Color.BLACK);

		int left = Math.min(viewportCornerA.x, viewportCornerB.x);
		int right = Math.max(viewportCornerA.x, viewportCornerB.x);
		int top = Math.min(viewportCornerA.y, viewportCornerB.y);
		int bottom = Math.max(viewportCornerA.y, viewportCornerB.y);

		canvas.drawRect(
			left, top,
			right - left,
			bottom - top
		);
	}

	private Point mouseToCanvas(Point pt) {
		Point res = new Point();
		if (display.isDoFlip()) {
			res.x = getHeight() - pt.y;
			res.y = pt.x;
		} else {
			res.x = pt.x;
			res.y = pt.y;
		}

		return res;
	}

	private void updateViewport() {
		if (viewportCornerA == null) return;

		Point canvasCornerA = mouseToCanvas(viewportCornerA);
		Point canvasCornerB = mouseToCanvas(viewportCornerB);

		int left = Math.min(canvasCornerA.x, canvasCornerB.x);
		int right = Math.max(canvasCornerA.x, canvasCornerB.x);
		int top = Math.min(canvasCornerA.y, canvasCornerB.y);
		int bottom = Math.max(canvasCornerA.y, canvasCornerB.y);

		if (right - left > 5 && bottom - top > 5) {
			Point2D.Double cornerA = display.canvasToData(new Point(left, top));
			Point2D.Double cornerB = display.canvasToData(new Point(right, bottom));

			display.updateViewport(new GraphicsViewport(
				Math.min(cornerA.x, cornerB.x),
				Math.max(cornerA.x, cornerB.x),
				Math.min(cornerA.y, cornerB.y),
				Math.max(cornerA.y, cornerB.y)
			));
		}

		viewportCornerA = null;
		viewportCornerB = null;
		repaint();
	}

	private void showNearestPoint(Point pt) {
		if (display.data.empty()) return;
		if (isMouseDown) return;

		pt = mouseToCanvas(pt);

		int minDist = 1_000_000;
		int minI = 0;

		for (int i = 0; i < display.data.points.length; i++) {
			Point ptCvs = display.dataToCanvas(display.data.points[i]);

			if (ptCvs.x < 0 || ptCvs.x > display.getWidthProxy() ||
				ptCvs.y < 0 || ptCvs.y > display.getHeightProxy()) {
				continue;
			}

			int dist = (ptCvs.x - pt.x) * (ptCvs.x - pt.x) + (ptCvs.y - pt.y) * (ptCvs.y - pt.y);
			if (dist < minDist) {
				minDist = dist;
				minI = i;
			}
		}

		if (minDist <= POINT_SELECTION_RADIUS * POINT_SELECTION_RADIUS) {
			selectedPointInd = minI;
		} else {
			selectedPointInd = -1;
		}
		repaint();
	}

	private void moveSelectedPoint(Point pt) {
		if (selectedPointInd == -1 || !isMouseDown) return;

		Point2D.Double ptData = display.canvasToData(mouseToCanvas(pt));

		display.data.updatePointY(selectedPointInd, ptData.y);
		display.repaint();
	}

	@Override
	public void mouseDragged(MouseEvent e) {
		showNearestPoint(e.getPoint());

		if (viewportCornerA != null) {
			viewportCornerB = e.getPoint();
			repaint();
		} else {
			moveSelectedPoint(e.getPoint());
		}
	}

	@Override
	public void mouseMoved(MouseEvent e) {
		showNearestPoint(e.getPoint());
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		if (e.getButton() == MouseEvent.BUTTON3) {
			display.previousViewport();
		}
	}

	@Override
	public void mousePressed(MouseEvent e) {
		if (e.getButton() != MouseEvent.BUTTON1) return;

		isMouseDown = true;

		if (selectedPointInd == -1) {
			viewportCornerA = viewportCornerB = e.getPoint();
		}
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		isMouseDown = false;

		updateViewport();
	}

	@Override
	public void mouseEntered(MouseEvent e) {

	}

	@Override
	public void mouseExited(MouseEvent e) {

	}
}
