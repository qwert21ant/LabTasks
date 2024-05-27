package ru.qwert21.labs.C9;

import jakarta.servlet.ServletConfig;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;

@WebServlet(value = "/", loadOnStartup = 1)
public class StartupServlet extends HttpServlet {
  private static final long serialVersionUID = 1L;

  public void init(ServletConfig config) throws ServletException {
    super.init(config);

    UserList userList = UserListHelper.readUserList(getServletContext());
    getServletContext().setAttribute("users", userList);
    AdList adList = AdListHelper.readAdList(getServletContext());
    getServletContext().setAttribute("ads", adList);
    for (Ad ad : adList.getAds()) {
      ad.setAuthor(userList.findUser(ad.getAuthorId()));
      ad.setLastModified(ad.getLastModified());
    }
  }
}