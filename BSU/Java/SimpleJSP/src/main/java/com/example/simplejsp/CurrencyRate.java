package com.example.simplejsp;

import java.util.HashMap;

public class CurrencyRate {
  private final String base;
  private final HashMap<String, Double> rates;

  public CurrencyRate(String base, HashMap<String, Double> rates) {
    this.base = base;
    this.rates = rates;
  }

  public String getBase() {
    return base;
  }

  public HashMap<String, Double> getRates() {
    return this.rates;
  }
}
