package ru.qwert21.labs.lab1C.food;

import ru.qwert21.labs.lab1C.Utils;

public class Sandwich extends Food {
  private String filling1;
  private String filling2;

  public Sandwich(String filling1, String filling2) {
    super("Sandwich");

    this.filling1 = filling1;
    this.filling2 = filling2;
  }

  public String getFilling1() {
    return filling1;
  }

  public void setFilling1(String filling1) {
    this.filling1 = filling1;
  }

  public String getFilling2() {
    return filling1;
  }

  public void setFilling2(String filling2) {
    this.filling2 = filling2;
  }

  @Override
  public int calculateCalories() {
    return 10 + filling1.length() + filling2.length();
  }

  @Override
  public boolean equals(Object obj) {
    if (!(obj instanceof Sandwich sandwich)) return false;

    return Utils.isEqual(filling1, sandwich.filling1) &&
            Utils.isEqual(filling2, sandwich.filling2);
  }

  @Override
  public String toString() {
    return super.toString() + " with " + filling1 + " & " + filling2;
  }
}
