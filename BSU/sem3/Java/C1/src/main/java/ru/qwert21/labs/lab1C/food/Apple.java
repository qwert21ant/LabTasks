package ru.qwert21.labs.lab1C.food;

import ru.qwert21.labs.lab1C.Utils;

public class Apple extends Food {
  private String size;

  public Apple(String size) {
    super("Apple");

    this.size = size;
  }

  public String getSize() {
    return size;
  }

  public void setSize(String size) {
    this.size = size;
  }

  @Override
  public int calculateCalories() {
    return size.length() / 2;
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Apple apple)) return false;

    return Utils.isEqual(size, apple.size);
  }

  @Override
  public String toString() {
    return super.toString() + " (" + size + ")";
  }
}
