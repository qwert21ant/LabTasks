package ru.qwert21.labs.C2;

import javax.swing.*;
import java.util.Objects;

public abstract class Constants {
	static public final String WINDOW_TITLE = "Вычисление формул";
	static public final int WINDOW_WIDTH = 800;
	static public final int WINDOW_HEIGHT = 300;
	static public final String BUTTON_FORMULA1 = "Формула 1";
	static public final String BUTTON_FORMULA2 = "Формула 2";

	static public final String BUTTON_VAR1 = "1: ";
	static public final String BUTTON_VAR2 = "2: ";
	static public final String BUTTON_VAR3 = "3: ";

	static public final String BUTTON_MEM_CLEAR = "MC";

	static public final String BUTTON_MEM_ADD = "M+";

	static public final String BUTTON_EVAL = "Вычислить";
	static public final String BUTTON_CLEAR = "Очистить";

	static public final ImageIcon ICON_FORMULA1 = new ImageIcon(
		Objects.requireNonNull(MyToolkit.loadImage("formula1.png"))
	);
	static public final ImageIcon ICON_FORMULA2 = new ImageIcon(
		Objects.requireNonNull(MyToolkit.loadImage("formula2.png"))
	);
}
