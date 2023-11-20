package ru.qwert21.labs.C3;

import javax.swing.*;
import javax.swing.border.BevelBorder;
import java.awt.*;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.Arrays;
import java.util.Objects;

import static ru.qwert21.labs.C3.MyToolkit.*;

public class MainFrame extends JFrame {
	private final JTextField fieldFrom, fieldTo, fieldStep;
	private final MyTableModel tableModel;
	private final MyTableCellRenderer tableCellRenderer;
	private final JTable table;

	private final JFileChooser fileChooser = new JFileChooser();

	private final JMenuItem[] switchableMenuItems = new JMenuItem[5];

	public MainFrame(double[] coefficients) {
		super(Constants.WINDOW_TITLE);

		setSize(Constants.WINDOW_WIDTH, Constants.WINDOW_HEIGHT);

		centerFrame();

		setLayout(new BorderLayout());

		Box topBox = createRow(
			Box.createHorizontalGlue(),
			new JLabel("Интервал: [ "),
			fieldFrom = createTextField(6, true),
			new JLabel("; "),
			fieldTo = createTextField(6, true),
			new JLabel("] "),
			Box.createHorizontalStrut(20),
			new JLabel("с шагом: "),
			fieldStep = createTextField(6, true),
			Box.createHorizontalGlue()
		);
		topBox.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		setVerticalPadding(topBox);

		Box bottomBox = createRow(
			Box.createHorizontalGlue(),
			createButton(Constants.BUTTON_EVAL, (e) -> evalPoly()),
			Box.createHorizontalStrut(20),
			createButton(Constants.BUTTON_CLEAR, (e) -> clearFields()),
			Box.createHorizontalGlue()
		);
		bottomBox.setBorder(BorderFactory.createBevelBorder(BevelBorder.LOWERED));
		setVerticalPadding(bottomBox);

		setJMenuBar(createMenuBar(
			createMenu("Файл",
				switchableMenuItems[0] = createMenuItem("Сохранить txt", false, (e) -> onMenuSaveTXTClick()),
				switchableMenuItems[1] = createMenuItem("Сохранить csv", false, (e) -> onMenuSaveCSVClick()),
				switchableMenuItems[2] = createMenuItem("Сохранить bin", false, (e) -> onMenuSaveBINClick())
			),
			createMenu("Таблица",
				switchableMenuItems[3] = createMenuItem("Найти значение", false, (e) -> onMenuFindClick()),
				switchableMenuItems[4] = createMenuItem("Найти из диапазона", false, (e) -> onMenuFindInRangeClick())
			),
			createMenu("Справка",
				createMenuItem("О программе", true, (e) -> onMenuAboutClick())
			)
		));

		tableModel = new MyTableModel(coefficients);
		tableCellRenderer = new MyTableCellRenderer();
		table = new JTable(tableModel);
		table.setDefaultRenderer(Double.class, tableCellRenderer);

		getContentPane().add(topBox, BorderLayout.NORTH);
		getContentPane().add(bottomBox, BorderLayout.SOUTH);
		getContentPane().add(new JScrollPane(table), BorderLayout.CENTER);

		clearFields();

		fileChooser.setCurrentDirectory(new File("."));

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}

	private void centerFrame() {
		Toolkit kit = Toolkit.getDefaultToolkit();

		Dimension screen = kit.getScreenSize();

		setLocation((screen.width - Constants.WINDOW_WIDTH) / 2, (screen.height - Constants.WINDOW_HEIGHT) / 2);
	}

	private void switchMenuItems(boolean enable) {
		Arrays.stream(switchableMenuItems).forEach((item) -> item.setEnabled(enable));
	}

	private void evalPoly() {
		try {
			double from = Double.parseDouble(fieldFrom.getText());
			double to = Double.parseDouble(fieldTo.getText());
			double step = Double.parseDouble(fieldStep.getText());

			if (from > to || step > (to - from))
				throw new Exception();

			tableModel.setFrom(from);
			tableModel.setTo(to);
			tableModel.setStep(step);
			tableModel.enable();

			tableModel.fireTableDataChanged();
			tableCellRenderer.clearSelectors();

			switchMenuItems(true);
		} catch (Exception e) {
			showInputError(this);
		}
	}

	private void clearFields() {
		fieldFrom.setText("0.0");
		fieldTo.setText("1.0");
		fieldStep.setText("0.1");

		tableModel.disable();
		tableModel.fireTableDataChanged();
		tableCellRenderer.clearSelectors();

		switchMenuItems(false);
	}

	private boolean chooseFile() {
		return fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION;
	}

	private void onMenuSaveTXTClick() {
		if (!chooseFile()) return;

		File file = fileChooser.getSelectedFile();
		try (PrintStream out = new PrintStream(new FileOutputStream(file))) {
			tableModel.print(out);
		} catch (Exception ignored) {}
	}

	private void onMenuSaveCSVClick() {
		if (!chooseFile()) return;

		File file = fileChooser.getSelectedFile();
		try (PrintStream out = new PrintStream(new FileOutputStream(file))) {
			tableModel.printCSV(out);
		} catch (Exception ignored) {}
	}

	private void onMenuSaveBINClick() {
		if (!chooseFile()) return;

		File file = fileChooser.getSelectedFile();
		try (DataOutputStream out = new DataOutputStream(new FileOutputStream(file))) {
			tableModel.printBIN(out);
		} catch (Exception ignored) {}
	}

	private void onMenuFindClick() {
		try {
			String str = JOptionPane.showInputDialog(this, "Введите значение",
				"Найти значение", JOptionPane.QUESTION_MESSAGE);

			Double value = Double.valueOf(str);

			tableCellRenderer.clearSelectors();
			tableCellRenderer.setFindValue(value);
			table.repaint();
		} catch (Exception e) {
			showInputError(this);
		}
	}

	private void onMenuFindInRangeClick() {
		try {
			String str = JOptionPane.showInputDialog(this, "Введите начало",
				"Найти значение в диапазоне", JOptionPane.QUESTION_MESSAGE);

			Double from = Double.valueOf(str);

			str = JOptionPane.showInputDialog(this, "Введите конец",
				"Найти значение в диапазоне", JOptionPane.QUESTION_MESSAGE);

			Double to = Double.valueOf(str);

			if (from > to) {
				throw new Exception();
			}

			tableCellRenderer.clearSelectors();
			tableCellRenderer.setFindRange(from, to);
			table.repaint();
		} catch (Exception e) {
			showInputError(this);
		}
	}

	private void onMenuAboutClick() {
		JOptionPane.showMessageDialog(this,
			createColumn(
				new JLabel("Антанович Александр"),
				new JLabel("6 группа")
			),
			"О программе", JOptionPane.INFORMATION_MESSAGE,
			new ImageIcon(
				resizeImageToWidth(
					Objects.requireNonNull(loadImage("img.png")),
					100
				)
			)
		);
	}
}
