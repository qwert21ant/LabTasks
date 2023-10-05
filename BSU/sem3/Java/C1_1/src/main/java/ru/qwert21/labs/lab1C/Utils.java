package ru.qwert21.labs.lab1C;

public class Utils {
  static public boolean isEqual(Object a, Object b) {
    if (a == b) return true;

    if (a != null) return a.equals(b);
    return false;
  }
}
