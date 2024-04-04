package ru.qwert21.labs.C4;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Point2D;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.util.LinkedList;
import java.util.List;

import static ru.qwert21.labs.C4.MyToolkit.*;

public class MainFrame extends JFrame {
	public static final String WINDOW_TITLE = "Построение графиков функций";
	public static final int WINDOW_WIDTH = 600;
	public static final int WINDOW_HEIGHT = 400;

	private final JCheckBoxMenuItem menuAxes, menuMarkers, menuAreas, menuFlip, menuStretch;

	private final JFileChooser fileChooser = new JFileChooser(new File("."));

	private final GraphicsDisplay display = new GraphicsDisplay();

	public MainFrame() {
		super(WINDOW_TITLE);

		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		centerFrame(this);

		setLayout(new BorderLayout());

		setJMenuBar(createMenuBar(
			createMenu("Файл",
				createMenuItem("Открыть", true, (e) -> onMenuOpen())
			),
			createMenu("График",
				menuAxes = createCheckBoxMenuItem("Показать оси",
					true, display.isShowAxes(), (e) -> onMenuAxes()),
				menuMarkers = createCheckBoxMenuItem("Показать маркеры",
					true, display.isShowMarkers(), (e) -> onMenuMarkers()),
				menuAreas = createCheckBoxMenuItem("Показать замкнутые области",
					true, display.isShowClosedAreas(), (e) -> onMenuAreas()),
				menuFlip = createCheckBoxMenuItem("Повернуть график",
					true, display.isDoFlip(), (e) -> onMenuFlip()),
				menuStretch = createCheckBoxMenuItem("Растянуть график",
					true, display.isDoStretch(), (e) -> onMenuStretch())
			)
		));

		getContentPane().add(display, BorderLayout.CENTER);

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}

	private boolean chooseFile() {
		return fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION;
	}

	private void onMenuOpen() {
		if (!chooseFile()) return;

		File file = fileChooser.getSelectedFile();
		try (DataInputStream in = new DataInputStream(new FileInputStream(file))) {
			List<Point2D.Double> data = new LinkedList<>();

			while (in.available() > 0) {
				data.add(new Point2D.Double(in.readDouble(), in.readDouble()));
			}

			Point2D.Double[] dataArr = new Point2D.Double[data.size()];

			display.setData(data.toArray(dataArr));
			display.repaint();
		} catch (Exception e) {
			showError(this, "Ошибка при чтении файла");
		}
	}

	private void onMenuAxes() {
		display.setShowAxes(menuAxes.getState());
		display.repaint();
	}

	private void onMenuMarkers() {
		display.setShowMarkers(menuMarkers.getState());
		display.repaint();
	}

	private void onMenuAreas() {
		display.setShowClosedAreas(menuAreas.getState());
		display.repaint();
	}

	private void onMenuFlip() {
		display.setDoFlip(menuFlip.getState());
		display.repaint();
	}

	private void onMenuStretch() {
		display.setDoStretch(menuStretch.getState());
		display.repaint();
	}
}
