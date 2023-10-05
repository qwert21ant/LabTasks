package ru.qwert21.labs.lab1C.food;

import ru.qwert21.labs.lab1C.Utils;

public class Cheese extends Food {
  public Cheese() {
    super("Cheese");
  }

  @Override
  public int calculateCalories() {
    return 23;
  }

  @Override
  public boolean equals(Object obj) {
    return obj instanceof Cheese;
  }
}
