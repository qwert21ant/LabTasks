package ru.qwert21.labs.C8;

import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.Calendar;

import static ru.qwert21.labs.C8.Constants.*;

@WebServlet("/" + SEND_MESSAGE_SERVLET)
public class SendMessageServlet extends ChatServlet {
  private static final long serialVersionUID = 1L;

  protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
    String message = request.getParameter("message");

    if (message == null || message.isEmpty()) {
      response.setStatus(400);
      response.getWriter().print("Bad request");
      response.getWriter().close();
      return;
    }

    String username = (String) request.getSession().getAttribute("name");

    if (username == null) {
      response.setStatus(403);
      response.getWriter().print("Unauthorized");
      response.getWriter().close();
      return;
    }

    ChatUser author = activeUsers.get(username);
    synchronized (messages) {
      messages.add(new ChatMessage(message, author, Calendar.getInstance().getTimeInMillis()));
    }

    response.setStatus(200);
    response.getWriter().close();
  }
}
