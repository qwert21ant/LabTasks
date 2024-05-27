package ru.qwert21.labs.C8;

import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

import static ru.qwert21.labs.C8.Constants.MESSAGES_SERVLET;

@WebServlet("/" + MESSAGES_SERVLET)
public class MessageListServlet extends ChatServlet {
  private static final long serialVersionUID = 1L;

  protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
    PrintWriter pw = response.getWriter();

    pw.print(
      "<html>" +
        "<head>" +
          "<meta charset='utf-8'>" +
          "<meta http-equiv='refresh' content='5'>" +
        "</head>" +
        "<body>"
    );

    SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm");

    for (int i = messages.size() - 1; i >= 0; i--) {
      ChatMessage aMessage = messages.get(i);

      pw.print(
        "<div>" +
          "<span style=\"font-family: monospace\">[" + sdf.format(new Date(aMessage.getTimestamp())) + "] </span>" +
          "<strong>" + aMessage.getAuthor().getName() +
          "</strong>: " + aMessage.getMessage() +
        "</div>"
      );
    }

    pw.print("</body></html>");
    pw.close();
  }
}
