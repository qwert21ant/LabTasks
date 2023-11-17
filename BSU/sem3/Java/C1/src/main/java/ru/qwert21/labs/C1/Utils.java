package ru.qwert21.labs.C1;

public class Utils {
  static public boolean isEqual(Object a, Object b) {
    if (a == b) return true;

    if (a != null) return a.equals(b);
    return false;
  }
}
