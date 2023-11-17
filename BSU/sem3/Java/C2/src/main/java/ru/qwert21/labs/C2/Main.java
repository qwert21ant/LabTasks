package ru.qwert21.labs.C2;

import static java.lang.Math.*;

public class Main {
	public static void main(String[] args) {
		new MainFrame(new Core(
			(x, y, z) -> sin(log(y) + sin(PI * y * y)) * pow(x * x + sin(z) + pow(E, cos(z)), 0.25),
			(x, y, z) -> pow(
					cos(pow(E, x)) +
					log((1 + y) * (1 + y)) +
					sqrt(pow(E, cos(x)) + sin(PI * z) * sin(PI * z)) +
					sqrt(1. / x) + cos(y * y),
				sin(z)
			)
		));
	}
}
