package ru.qwert21.labs.C9.tags;

import jakarta.servlet.jsp.JspException;
import jakarta.servlet.jsp.PageContext;
import jakarta.servlet.jsp.tagext.SimpleTagSupport;
import ru.qwert21.labs.C9.User;
import ru.qwert21.labs.C9.UserList;
import ru.qwert21.labs.C9.UserListHelper;

import java.io.IOException;

public class AddUser extends SimpleTagSupport {
  private User user;

  public void setUser(User user) {
    this.user = user;
  }

  public void doTag() throws JspException, IOException {
    String errorMessage = null;
    UserList userList = (UserList) getJspContext().getAttribute("users", PageContext.APPLICATION_SCOPE);

    if (user.getLogin() == null || user.getLogin().equals("")) {
      errorMessage = "Логин не может быть пустым!";
    } else {
      if (user.getName() == null || user.getName().equals("")) {
        user.setName(user.getLogin());
//        errorMessage = "Имя пользователя не может быть пустым!";
      }
    }

    if (errorMessage == null) {
      try {
        userList.addUser(user);
        UserListHelper.saveUserList(userList);
      } catch (UserList.UserExistsException e) {
        errorMessage = "Пользователь с таким логином уже существует!";
      }
    }

    getJspContext().setAttribute("errorMessage", errorMessage, PageContext.SESSION_SCOPE);
  }
}

