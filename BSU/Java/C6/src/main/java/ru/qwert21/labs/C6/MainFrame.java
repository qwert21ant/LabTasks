package ru.qwert21.labs.C6;

import javax.swing.*;
import java.awt.*;

import static ru.qwert21.labs.C6.MyToolkit.*;

public class MainFrame extends JFrame {
  public static final String WINDOW_TITLE = "Мячи";
  public static final int WINDOW_WIDTH = 600;
  public static final int WINDOW_HEIGHT = 400;

  private final JMenuItem menuPauseMovement, menuResumeMovement;

  private final Field field = new Field();

  public MainFrame() {
    super(WINDOW_TITLE);

    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    centerFrame(this);

    setLayout(new BorderLayout());

    setJMenuBar(createMenuBar(
      createMenu("Мячи",
        createMenuItem("Добавить мяч", true, (e) -> field.addBall())
      ),
      createMenu("Управление",
        menuPauseMovement = createMenuItem("Приостановить движение",
          true, (e) -> onPauseMovement()),
        menuResumeMovement = createMenuItem("Возобновить движение",
          false, (e) -> onResumeMovement())
      )
    ));

    getContentPane().add(field, BorderLayout.CENTER);

    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setVisible(true);
  }

  public static void main(String[] args) {
    new MainFrame();
  }

  private void onPauseMovement() {
    menuPauseMovement.setEnabled(false);
    menuResumeMovement.setEnabled(true);

    field.pause();
  }

  private void onResumeMovement() {
    menuPauseMovement.setEnabled(true);
    menuResumeMovement.setEnabled(false);

    field.resume();
  }
}
