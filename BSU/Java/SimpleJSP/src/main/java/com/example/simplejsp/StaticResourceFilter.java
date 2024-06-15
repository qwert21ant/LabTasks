package com.example.simplejsp;

import jakarta.servlet.Filter;
import jakarta.servlet.FilterChain;
import jakarta.servlet.ServletException;
import jakarta.servlet.ServletRequest;
import jakarta.servlet.ServletResponse;
import jakarta.servlet.annotation.WebFilter;
import jakarta.servlet.http.HttpServletRequest;

import java.io.IOException;

@WebFilter(filterName = "staticResourceFilter", value = "/*")
public class StaticResourceFilter implements Filter {

  @Override
  public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
    throws IOException, ServletException {
    HttpServletRequest httpRequest = (HttpServletRequest) request;
    String path = httpRequest.getRequestURI().substring(httpRequest.getContextPath().length());

    if (path.startsWith("/css/") || path.startsWith("/js/") || path.startsWith("/images/")) {
      chain.doFilter(request, response);
    } else {
      request.getRequestDispatcher("/currency-rate").forward(request, response);
    }
  }
}