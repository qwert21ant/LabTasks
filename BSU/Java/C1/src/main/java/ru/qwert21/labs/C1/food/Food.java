package ru.qwert21.labs.C1.food;

import ru.qwert21.labs.C1.Consumable;
import ru.qwert21.labs.C1.Nutritious;
import ru.qwert21.labs.C1.Utils;

abstract public class Food implements Consumable, Nutritious {
  private String name;

  public Food(String name) {
    this.name = name;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  @Override
  public void consume() {
    System.out.println("- " + this);
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Food food)) return false;

    return Utils.isEqual(name, food.name);
  }

  @Override
  public String toString() {
    return name;
  }
}
