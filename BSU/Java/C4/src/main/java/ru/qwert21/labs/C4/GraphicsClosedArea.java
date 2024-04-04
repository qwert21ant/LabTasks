package ru.qwert21.labs.C4;

import java.awt.geom.Point2D;

public class GraphicsClosedArea {
	public int leftInd;
	public int rightInd;
	public double area;

	public double leftX;
	public double rightX;
	public Point2D.Double center;

	public GraphicsClosedArea(int leftInd, int rightInd, double area, double leftX, double rightX, Point2D.Double center) {
		this.leftInd = leftInd;
		this.rightInd = rightInd;
		this.area = area;
		this.leftX = leftX;
		this.rightX = rightX;
		this.center = center;
	}
}
