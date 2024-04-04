package ru.qwert21.labs.C1;

import ru.qwert21.labs.C1.food.Food;

import java.lang.reflect.Constructor;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

public class Main {
  static public void main(String[] args) {
    boolean countCalories = false;
    boolean useSort = false;
    Food countPattern = null;
    List<Food> breakfast = new ArrayList<>();

    for (int i = 0; i < args.length; i++) {
      String arg = args[i];

      switch (arg) {
        case "-calories" -> countCalories = true;
        case "-sort" -> useSort = true;
        case "-count" -> {
          if (i + 1 < args.length) {
            countPattern = instFood(args[i + 1]);
            i++;
          }
        }
        default -> {
          Food food = instFood(arg);
          if (food != null) {
            breakfast.add(food);
          }
        }
      }
    }

    if (useSort) {
      breakfast.sort(new Comparator<Food>() {
        @Override
        public int compare(Food a, Food b) {
          return a.getName().length() - b.getName().length();
        }
      });
    }

    System.out.println("Breakfast:");
    breakfast.forEach(Consumable::consume);

    if (countCalories) {
      int total = breakfast.stream().<Integer>reduce(0,
              (a, b) -> a + b.calculateCalories(),
              Integer::sum);

      System.out.println("Total calories: " + total);
    }

    if (countPattern != null) {
      int cnt1 = countSameAs(breakfast, countPattern);
      int cnt2 = countByClass(breakfast, countPattern.getClass());

      System.out.println("Count of \"" + countPattern + "\": " + cnt1);
      System.out.println("Count of \"" + countPattern.getClass().getSimpleName() + "\": " + cnt2);
    }
  }

  static private int countByClass(List<Food> data, Class<?> cls) {
    int res = 0;
    for (Food food : data) {
      if (food.getClass() == cls) {
        res++;
      }
    }
    return res;
  }

  static private int countSameAs(List<Food> data, Food match) {
    int res = 0;
    for (Food food : data) {
      if (match.equals(food)) {
        res++;
      }
    }
    return res;
  }

  static private Food instFood(String desc) {
    String[] parts = desc.split("/");

    try {
      Class<?> cls = Class.forName("ru.qwert21.labs.lab1C.food." + parts[0]);

      if (cls.getSuperclass() != Food.class) {
        System.out.println(parts[0] + " is not a food");
        return null;
      }

      Constructor<?>[] cons = cls.getConstructors();

      Object[] params = parts.length == 1 ?
              new Object[0] :
              Arrays.copyOfRange(parts, 1, parts.length);

      return (Food) cons[0].newInstance(params);
    } catch (ClassNotFoundException e) {
      System.out.println(parts[0] + " not found. skip");
    } catch (IllegalArgumentException e) {
      System.out.println("Incorrect params for " + parts[0] + ": " + desc);
    } catch (Exception e) {
      System.out.println("Something went wrong with " + parts[0]);
    }
    return null;
  }
}
