package ru.qwert21.labs.C5.display;

import java.awt.*;

import static ru.qwert21.labs.C5.MyToolkit.createSimpleStroke;

public abstract class GraphicsDisplayStyle {
	public static final Stroke strokeGraphics = new BasicStroke(2.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
		10.f, new float[]{8, 3, 2, 3, 2, 3, 4, 3, 4, 3}, 0.f);
	public static final Stroke strokeAxes = createSimpleStroke(2.f);
	public static final Stroke strokeArrows = createSimpleStroke(4.f);
	public static final Stroke strokeMarkers = createSimpleStroke(1.f);

	public static final Stroke strokeSelecting = new BasicStroke(2.f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND,
		10.f, new float[]{4, 4}, 0.f);

	public static final Color colorGraphics = new Color(0xdd4444);
	public static final Color colorAxes = Color.BLACK;
	public static final Color colorMarkers = colorGraphics;
	public static final Color colorMarkersHighlighted = new Color(0x4444dd);
	public static final Color colorAreas = new Color(0x66ff66);

	public static final Font fontCommon = new Font("Verdana", Font.BOLD, 12);
}
