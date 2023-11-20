package ru.qwert21.labs.C3;

public class Main {
	public static void main(String[] args) {
		try {
			if (args.length == 0) {
				throw new Exception();
			}

			double[] coefficients = new double[args.length];
			for (int i = 0; i < args.length; i++) {
				coefficients[i] = Double.parseDouble(args[i]);
			}

			new MainFrame(coefficients);
		} catch (Exception e) {
			System.out.println("Неверные данные");
		}
	}
}
