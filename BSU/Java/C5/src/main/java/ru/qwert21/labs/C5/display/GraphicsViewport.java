package ru.qwert21.labs.C5.display;

public class GraphicsViewport implements Cloneable {
	public double minX;
	public double maxX;
	public double minY;
	public double maxY;

	public GraphicsViewport() {}

	public GraphicsViewport(double minX, double maxX, double minY, double maxY) {
		this.minX = minX;
		this.maxX = maxX;
		this.minY = minY;
		this.maxY = maxY;
	}

	@Override
	public GraphicsViewport clone() {
		try {
			return (GraphicsViewport) super.clone();
		} catch (CloneNotSupportedException e) {
			throw new AssertionError();
		}
	}
}
