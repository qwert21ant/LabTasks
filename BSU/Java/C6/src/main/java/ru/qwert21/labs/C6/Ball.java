package ru.qwert21.labs.C6;

import java.awt.*;
import java.awt.geom.Ellipse2D;
import java.awt.geom.Point2D;

import static ru.qwert21.labs.C6.Constants.*;

public class Ball implements Runnable {
  public double radius;
  public Point2D.Double pos;
  public Point2D.Double velocity;
  private Color color;
  private Field field;

  public Ball(Field field, double radius, Point2D.Double pos, Point2D.Double velocity, Color color) {
    this.field = field;
    this.radius = radius;
    this.pos = (Point2D.Double) pos.clone();
    this.velocity = (Point2D.Double) velocity.clone();
    this.color = new Color(color.getRGB());

    Thread thread = new Thread(this);
    thread.start();
  }

  public static Ball createRandom(Field field) {
    double radius = Math.random() * (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS;

    return new Ball(
      field, radius,
      new Point2D.Double(
        Math.random() * (field.getWidth() - 2 * radius) + radius,
        Math.random() * (field.getHeight() - 2 * radius) + radius
      ),
      new Point2D.Double(
        Math.random() * (MAX_VELOCITY - MIN_VELOCITY) + MIN_VELOCITY,
        Math.random() * (MAX_VELOCITY - MIN_VELOCITY) + MIN_VELOCITY
      ),
      new Color((int) (Math.random() * 0xffffff))
    );
  }

  private void move() {
    pos.x += velocity.x;
    pos.y += velocity.y;

    if (pos.x + radius > field.getWidth()) {
      pos.x = field.getWidth() - radius;
      velocity.x = -velocity.x;
    } else if (pos.x < radius) {
      pos.x = radius;
      velocity.x = -velocity.x;
    }

    if (pos.y + radius > field.getHeight()) {
      pos.y = field.getHeight() - radius;
      velocity.y = -velocity.y;
    } else if (pos.y < radius) {
      pos.y = radius;
      velocity.y = -velocity.y;
    }
  }

  @Override
  public void run() {
    try {
      while (true) {
        field.canMove();

        move();

        Thread.sleep(10);
      }
    } catch (InterruptedException e) {
      throw new RuntimeException(e);
    }
  }

  public void paint(Graphics2D canvas) {
    canvas.setColor(color);
    canvas.setPaint(color);

    canvas.fillOval((int) (pos.x - radius), (int) (pos.y - radius), (int) (2 * radius), (int) (2 * radius));
  }
}
