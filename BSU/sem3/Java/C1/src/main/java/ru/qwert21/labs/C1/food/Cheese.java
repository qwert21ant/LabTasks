package ru.qwert21.labs.C1.food;

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
