package ru.qwert21.labs.C8;

import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.Calendar;

import static ru.qwert21.labs.C8.Constants.*;

@WebServlet("/" + LOGIN_SERVLET)
public class LoginServlet extends ChatServlet {
  private static final long serialVersionUID = 1L;
  private int sessionTimeout = 10 * 60;

  public void init() throws ServletException {
    super.init();

    String value = getServletConfig().getInitParameter("SESSION_TIMEOUT");

    if (value != null) {
      sessionTimeout = Integer.parseInt(value);
    }
  }

  @Override
  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String name = (String) request.getSession().getAttribute("name");

    String errorMessage = (String) request.getSession().getAttribute("error");

    String previousSessionId = null;

    if (name == null) {
      for (Cookie aCookie : request.getCookies()) {
        if (aCookie.getName().equals("sessionId")) {
          previousSessionId = aCookie.getValue();
          break;
        }
      }
      if (previousSessionId != null) {
        for (ChatUser aUser : activeUsers.values()) {
          if (aUser.getSessionId().equals(previousSessionId)) {
            name = aUser.getName();
            aUser.setSessionId(request.getSession().getId());
          }
        }
      }
    }

    if (name != null && !name.isEmpty()) {
      errorMessage = processLogonAttempt(name, request, response);
    }

    PrintWriter pw = response.getWriter();

    String content =
      "<html>" +
        "<head>" +
          "<meta charset='utf-8'>" +
          "<title>Чат</title>" +
        "</head>" +
        "<body>";

    if (errorMessage != null) {
      content +=
        "<p>" +
          "<font color='red'>" + errorMessage + "</font>" +
        "</p>";
    }

    content +=
      "<form method='post'>" +
        "Введите имя: " +
        "<input type='text' name='name' value=''>" +
        "<input type='submit' value='Войти в чат'>" +
      "</form>";

    content += "</body></html>";

    pw.print(content);
    pw.close();

    request.getSession().setAttribute("error", null);
  }

  @Override
  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String name = request.getParameter("name");

    String errorMessage;
    if (name == null || "".equals(name)) {
      errorMessage = "Имя пользователя не может быть пустым!";
    } else {
      errorMessage = processLogonAttempt(name, request, response);
    }

    if (errorMessage != null) {
      request.getSession().setAttribute("name", null);
      request.getSession().setAttribute("error", errorMessage);

      response.sendRedirect(LOGIN_SERVLET);
    }
  }

  String processLogonAttempt(String name, HttpServletRequest request, HttpServletResponse response) throws IOException {
    String sessionId = request.getSession().getId();

    ChatUser aUser = activeUsers.get(name);
    if (aUser == null) {
      aUser = new ChatUser(name, Calendar.getInstance().getTimeInMillis(), sessionId);

      synchronized (activeUsers) {
        activeUsers.put(aUser.getName(), aUser);
      }
    }
    if (aUser.getSessionId().equals(sessionId) ||
      aUser.getLastInteractionTime() < (Calendar.getInstance().getTimeInMillis() - sessionTimeout * 1000L)) {

      request.getSession().setAttribute("name", name);
      aUser.setLastInteractionTime(Calendar.getInstance().getTimeInMillis());
      Cookie sessionIdCookie = new Cookie("sessionId", sessionId);

      sessionIdCookie.setMaxAge(60 * 60 * 24 * 365);

      response.addCookie(sessionIdCookie);
      response.sendRedirect(MAIN_PAGE);
      return null;
    } else {
      return "Извините, но имя <strong>" + name + "</strong> уже кем-то занято. Пожалуйста выберите другое имя!";
    }
  }
}