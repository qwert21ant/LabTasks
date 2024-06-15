package com.example.simplejsp;

import java.io.*;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;

import com.google.gson.Gson;
import jakarta.servlet.ServletException;
import jakarta.servlet.http.*;
import jakarta.servlet.annotation.*;

@WebServlet(name = "currencyRateServlet", value = "/currency-rate")
public class CurrencyRateServlet extends HttpServlet {
  private static final String API_URL = "https://api.exchangerate-api.com/v4/latest/";
  private static final ArrayList<String> currencies;

  static {
    currencies = new ArrayList<String>();
    currencies.add("USD");
    currencies.add("EUR");
    currencies.add("RUB");
  }

  public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
    CurrencyRate rate = fetchCurrencyRate("BYN");
    request.setAttribute("rate", rate);
    request.getRequestDispatcher("/currencyRate.jsp").forward(request, response);
  }

  private CurrencyRate fetchCurrencyRate(String base) throws IOException {
    URL url = new URL(API_URL + base);
    HttpURLConnection connection = (HttpURLConnection) url.openConnection();
    connection.setRequestMethod("GET");

    int responseCode = connection.getResponseCode();
    if (responseCode == HttpURLConnection.HTTP_OK) {
      String jsonResponse = this.readStream(connection.getInputStream());
      return filterCurrencies(parseResponse(jsonResponse));
    } else {
      throw new IOException("Failed to fetch currency rate: " + responseCode);
    }
  }

  private String readStream(InputStream stream) throws IOException {
    try (BufferedReader reader = new BufferedReader(new InputStreamReader(stream))) {
      StringBuilder sb = new StringBuilder();
      String line;
      while ((line = reader.readLine()) != null) {
        sb.append(line);
      }
      return sb.toString();
    }
  }

  private CurrencyRate parseResponse(String jsonResponse) {
    Gson gson = new Gson();

    return gson.fromJson(jsonResponse, CurrencyRate.class);
  }

  private CurrencyRate filterCurrencies(CurrencyRate currencyRate) {
    HashMap<String, Double> rates = currencyRate.getRates();
    HashMap<String, Double> filteredRates = new HashMap<String, Double>();
    for (String currency : currencies) {
      filteredRates.put(currency, rates.get(currency));
    }

    return new CurrencyRate(currencyRate.getBase(), filteredRates);
  }
}