package ru.qwert21.labs.C5.display;

import java.awt.geom.Point2D;
import java.io.*;
import java.util.LinkedList;
import java.util.List;

public class GraphicsData {
	Point2D.Double[] points;

	GraphicsViewport defaultViewport = new GraphicsViewport();

	final List<GraphicsClosedArea> areas = new LinkedList<>();

	public GraphicsData() {}

	public boolean empty() {
		return points == null;
	}

	public void updatePointY(int ind, double y) {
		points[ind].y = y;
		update();
	}

	private void update() {
		defaultViewport.minX = points[0].x;
		defaultViewport.maxX = points[points.length - 1].x;
		defaultViewport.minY = points[0].y;
		defaultViewport.maxY = points[0].y;

		for (int i = 1; i < points.length; i++) {
			defaultViewport.minY = Math.min(defaultViewport.minY, points[i].y);
			defaultViewport.maxY = Math.max(defaultViewport.maxY, points[i].y);
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
		for (int i = 1; i < points.length; i++) {
			if (points[i].y * points[i - 1].y <= 0) {
				double ptX = points[i].x - Math.abs((points[i].y) / (points[i].y - points[i - 1].y) * (points[i].x - points[i - 1].x));

				if (isStartArea) {
					curArea += 0.5 * (ptX - points[i - 1].x) * (points[i - 1].y);

					areas.add(new GraphicsClosedArea(
						prevCtrl, i - 1, curArea,
						nextLeftX, ptX, new Point2D.Double((ptX + nextLeftX) / 2, maxY / 2 * (points[prevCtrl].y < 0 ? -1 : 1))
					));
				}

				isStartArea = true;
				curArea = 0.5 * (points[i].x - ptX) * (points[i].y);
				nextLeftX = ptX;
				prevCtrl = i;
				maxY = 0;
			} else {
				curArea += 0.5 * (points[i].x - points[i - 1].x) * (points[i].y + points[i - 1].y);
			}

			maxY = Math.max(Math.abs(maxY), Math.abs(points[i].y));
		}
	}

	public void openFromFile(File file) throws IOException {
		try (DataInputStream in = new DataInputStream(new FileInputStream(file))) {
			List<Point2D.Double> data = new LinkedList<>();

			while (in.available() > 0) {
				data.add(new Point2D.Double(in.readDouble(), in.readDouble()));
			}

			points = new Point2D.Double[data.size()];

			data.toArray(points);
			update();
		}
	}

	public void saveToFile(File file) throws IOException {
		try (DataOutputStream out = new DataOutputStream(new FileOutputStream(file))) {
			for (Point2D.Double pt : points) {
				out.writeDouble(pt.x);
				out.writeDouble(pt.y);
			}
		}
	}
}
