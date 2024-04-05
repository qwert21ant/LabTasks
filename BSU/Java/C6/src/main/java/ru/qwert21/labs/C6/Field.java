package ru.qwert21.labs.C6;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.List;

import static ru.qwert21.labs.C6.Constants.VELOCITY_COEF;

public class Field extends JPanel implements MouseListener {
  private List<Ball> balls = new ArrayList<>();
  private boolean isPaused = false;

  public Field() {
    setBackground(Color.WHITE);

    this.setLayout(new BorderLayout());

    this.addMouseListener(this);

    Timer timer = new Timer(10, (event) -> this.repaint());
    timer.start();
  }

  public void addBall() {
    balls.add(Ball.createRandom(this));
  }

  public void pause() {
    isPaused = true;
  }

  public synchronized void resume() {
    if (!isPaused) return;

    isPaused = false;
    notifyAll();
  }

  public synchronized void canMove() throws InterruptedException {
    if (isPaused) wait();
  }

  @Override
  protected void paintComponent(Graphics g) {
    super.paintComponent(g);

    Graphics2D canvas = (Graphics2D) g;

    for (Ball ball : balls)
      ball.paint(canvas);
  }

  private Ball selectedBall = null;
  private Point firstPoint = null;

  private Ball getBallAtPos(Point p) {
    for (Ball ball : balls) {
      double dx = ball.pos.x - p.x;
      double dy = ball.pos.y - p.y;

      if (dx * dx + dy * dy <= ball.radius * ball.radius)
        return ball;
    }

    return null;
  }

  @Override
  public void mouseClicked(MouseEvent e) {
  }

  @Override
  public void mousePressed(MouseEvent e) {
    if (isPaused) return;
    if (e.getButton() != MouseEvent.BUTTON1) return;

    firstPoint = e.getPoint();
    selectedBall = getBallAtPos(firstPoint);
    if (selectedBall == null) return;

    pause();
  }

  @Override
  public void mouseReleased(MouseEvent e) {
    if (selectedBall == null || firstPoint == null) return;

    Point secondPoint = e.getPoint();

    double dx = secondPoint.x - firstPoint.x;
    double dy = secondPoint.y - firstPoint.y;

    selectedBall.velocity.x = dx / VELOCITY_COEF;
    selectedBall.velocity.y = dy / VELOCITY_COEF;

    selectedBall = null;
    resume();
  }

  @Override
  public void mouseEntered(MouseEvent e) {
  }

  @Override
  public void mouseExited(MouseEvent e) {
  }
}
