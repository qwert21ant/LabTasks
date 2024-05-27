package ru.qwert21.labs.C8;

import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.Cookie;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;

import static ru.qwert21.labs.C8.Constants.*;

@WebServlet("/" + LOGOUT_SERVLET)
public class LogoutServlet extends ChatServlet {
  private static final long serialVersionUID = 1L;

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String name = (String) request.getSession().getAttribute("name");

    if (name != null) {
      ChatUser aUser = activeUsers.get(name);

      if (aUser.getSessionId().equals(request.getSession().getId())) {
        synchronized (activeUsers) {
          activeUsers.remove(name);
        }

        request.getSession().setAttribute("name", null);
        response.addCookie(new Cookie("sessionId", null));
      }
    }

    response.sendRedirect(LOGIN_SERVLET);
    response.getWriter().close();
  }
}
