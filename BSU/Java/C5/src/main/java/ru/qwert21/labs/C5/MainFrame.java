package ru.qwert21.labs.C5;

import ru.qwert21.labs.C5.display.GraphicsDisplay;

import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

import static ru.qwert21.labs.C5.MyToolkit.*;

public class MainFrame extends JFrame {
	public static final String WINDOW_TITLE = "Построение графиков функций";
	public static final int WINDOW_WIDTH = 600;
	public static final int WINDOW_HEIGHT = 400;

	private final JMenuItem menuSave;
	private final JCheckBoxMenuItem menuAxes, menuMarkers, menuAreas, menuFlip;

	private final JFileChooser fileChooser = new JFileChooser(new File("."));

	private final GraphicsDisplay display = new GraphicsDisplay();

	public MainFrame() {
		super(WINDOW_TITLE);

		setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
		centerFrame(this);

		setLayout(new BorderLayout());

		setJMenuBar(createMenuBar(
			createMenu("Файл",
				createMenuItem("Открыть", true, (e) -> onMenuOpen()),
				menuSave = createMenuItem("Сохранить", false, (e) -> onMenuSave())
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
				createMenuItem("Восстановить соотношение",
					true, (e) -> onMenuRatio()),
				createMenuItem("Показать весь график",
				true, (e) -> onMenuShowAll())
			)
		));

		getContentPane().add(display, BorderLayout.CENTER);

//		openDefault();

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);
	}

	private boolean chooseFile() {
		return fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION;
	}

	private void openDefault() {
		try {
			display.openFromFile(new File("../sharedData/data.bin"));
			menuSave.setEnabled(true);
		} catch (IOException e) {
			showError(this, "Ошибка при чтении файла");
		}
	}

	private void onMenuOpen() {
		if (!chooseFile()) return;

		try {
			display.openFromFile(fileChooser.getSelectedFile());
			menuSave.setEnabled(true);
		} catch (IOException e) {
			showError(this, "Ошибка при чтении файла");
		}
	}

	private void onMenuSave() {
		if (!chooseFile()) return;

		try {
			display.saveToFile(fileChooser.getSelectedFile());
		} catch (IOException e) {
			showError(this, "Ошибка при записи файла");
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

	private void onMenuRatio() {
		display.restoreRatio();
		display.repaint();
	}

	private void onMenuShowAll() {
		display.showAll();
		display.repaint();
	}
}
