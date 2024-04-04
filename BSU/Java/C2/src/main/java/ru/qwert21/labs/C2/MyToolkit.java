package ru.qwert21.labs.C2;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.net.URL;

public abstract class MyToolkit {
  static public Image loadImage(String filename) {
    URL url = MyToolkit.class.getResource(filename);
    if (url == null) {
      return null;
    }

    try {
      return ImageIO.read(url);
    } catch(IOException e) {
      return null;
    }
  }

  static public Image resizeImageToWidth(Image img, int width) {
    int h = img.getHeight(null);
    int w = img.getWidth(null);

    double ratio = (double) w / h;

    return img.getScaledInstance(width, (int) (width / ratio), Image.SCALE_SMOOTH);
  }

  static public JTextField createTextField(int columns, boolean isEditable) {
    JTextField tf = new JTextField(columns);
    tf.setMaximumSize(tf.getPreferredSize());
    tf.setEditable(isEditable);
    return tf;
  }

  static public Box createRow(Component... comps) {
    Box box = Box.createHorizontalBox();

    for (Component comp : comps) {
      box.add(comp);
    }

    return box;
  }

  static public Box createColumn(Component... comps) {
    Box box = Box.createVerticalBox();

    for (Component comp : comps) {
      box.add(comp);
    }

    return box;
  }

  static public JComponent makeXCentered(JComponent comp) {
    comp.setAlignmentX(Component.CENTER_ALIGNMENT);
    return comp;
  }

  static public JButton createButton(String title, ActionListener listener) {
    JButton btn = new JButton(title);
    btn.addActionListener(listener);
    return btn;
  }

  static public JRadioButton createRadioButton(String title, boolean isSelected, ButtonGroup group, ActionListener listener) {
    JRadioButton btn = new JRadioButton(title, isSelected);
    btn.addActionListener(listener);
    group.add(btn);
    return btn;
  }
}
