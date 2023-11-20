package ru.qwert21.labs.C3;

import javax.swing.table.AbstractTableModel;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Locale;

public class MyTableModel extends AbstractTableModel {
	private final double[] coefficients;

	private double from = 0;
	private double to = 0;
	private double step = 0;

	private boolean enabled = false;

	public MyTableModel(double[] coefficients) {
		this.coefficients = coefficients;
	}

	public void setFrom(double from) {
		this.from = from;
	}

	public void setTo(double to) {
		this.to = to;
	}

	public void setStep(double step) {
		this.step = step;
	}

	public void disable() {
		enabled = false;
	}

	public void enable() {
		enabled = true;
	}
	@Override
	public int getRowCount() {
		if (!enabled) {
			return 0;
		}
		return (int) ((to - from) / step) + 1;
	}

	@Override
	public int getColumnCount() {
		return 4;
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		double x = from + step * rowIndex;

		return switch (columnIndex) {
			case 0 -> x;
			case 1 -> evalA(x);
			case 2 -> evalB(x);
			case 3 -> evalC(x);
			default -> null;
		};
	}

	@Override
	public String getColumnName(int column) {
		return switch (column) {
			case 0 -> "X";
			case 1 -> "Y";
			case 2 -> "Y'";
			case 3 -> "Y - Y'";
			default -> "";
		};
	}

	@Override
	public Class<?> getColumnClass(int columnIndex) {
		return Double.class;
	}

	private double evalA(double x) {
		double res = coefficients[coefficients.length - 1];

		for (int i = coefficients.length - 2; i >= 0; i--) {
			res *= x;
			res += coefficients[i];
		}

		return res;
	}

	private double evalB(double x) {
		double res = coefficients[0];

		for (int i = 1; i < coefficients.length; i++) {
			res *= x;
			res += coefficients[i];
		}

		return res;
	}

	private double evalC(double x) {
		return evalA(x) - evalB(x);
	}

	public void print(PrintStream out) {
		out.print("Многочлен: ");
		out.print(coefficients[0]);
		for (int i = 1; i < coefficients.length; i++) {
			out.print(" + " + coefficients[i] + "*X^" + i);
		}
		out.println();
		out.println("====================================================================================");
		for (int i = 0; i < getRowCount(); i++) {
			out.format(Locale.US, "%20.5f ", (Double) getValueAt(i, 0));
			out.format(Locale.US, "%20.5f ", (Double) getValueAt(i, 1));
			out.format(Locale.US, "%20.5f ", (Double) getValueAt(i, 2));
			out.format(Locale.US, "%20.5f%n", (Double) getValueAt(i, 3));
		}
	}

	public void printCSV(PrintStream out) {
		for (int i = 0; i < getRowCount(); i++) {
			out.print(getValueAt(i, 0) + ",");
			out.print(getValueAt(i, 1) + ",");
			out.print(getValueAt(i, 2) + ",");
			out.println(getValueAt(i, 3));
		}
	}

	public void printBIN(DataOutputStream out) throws IOException {
		for (int i = 0; i < getRowCount(); i++) {
			out.writeDouble((Double) getValueAt(i, 0));
			out.writeDouble((Double) getValueAt(i, 1));
			out.writeDouble((Double) getValueAt(i, 2));
			out.writeDouble((Double) getValueAt(i, 3));
		}
	}
}
