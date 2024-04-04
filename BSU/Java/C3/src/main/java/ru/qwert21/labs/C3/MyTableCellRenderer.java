package ru.qwert21.labs.C3;

import javax.swing.*;
import javax.swing.table.TableCellRenderer;
import java.awt.*;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.NumberFormat;
import java.util.Objects;

public class MyTableCellRenderer implements TableCellRenderer {
	private final DecimalFormat formatter;

	private Double findValue;
	private final Double[] findRange = new Double[2];

	private final JPanel panel = new JPanel(new BorderLayout());
	private final JLabel label = new JLabel();

	public MyTableCellRenderer() {
		formatter = (DecimalFormat) NumberFormat.getInstance();
		DecimalFormatSymbols decimalFormatSymbols = formatter.getDecimalFormatSymbols();
		decimalFormatSymbols.setDecimalSeparator('.');
		formatter.setDecimalFormatSymbols(decimalFormatSymbols);
		formatter.setGroupingUsed(false);
		formatter.setMaximumFractionDigits(5);

		panel.add(label);
	}

	public void setFindValue(Double value) {
		findValue = value;
	}

	public void setFindRange(Double from, Double to) {
		findRange[0] = from;
		findRange[1] = to;
	}

	public void clearSelectors() {
		findValue = null;
		findRange[0] = null;
		findRange[1] = null;
	}

	@Override
	public Component getTableCellRendererComponent(JTable table, Object obj, boolean isSelected, boolean hasFocus, int row, int column) {
		String str = formatter.format(obj);
		Double value = Double.valueOf(str);

		label.setText(str);

		if ((row + column) % 2 == 0) {
			label.setForeground(Color.BLACK);
			panel.setBackground(Color.WHITE);
		} else {
			label.setForeground(Color.WHITE);
			panel.setBackground(Color.BLACK);
		}

		if (column == 1 || column == 2) {
			if (findValue != null) {
				if (findValue.equals(value)) {
					label.setForeground(Color.WHITE);
					panel.setBackground(Color.RED);
				}
			}

			if (findRange[0] != null) {
				if (findRange[0] <= value && value <= findRange[1]) {
					label.setForeground(Color.WHITE);
					panel.setBackground(Color.RED);
				}
			}
		}

		return panel;
	}
}
