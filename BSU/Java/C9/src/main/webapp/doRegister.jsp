<%@page language="java" pageEncoding="UTF-8" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@taglib prefix="ad" uri="http://ru.qwert21.labs.C9.tags/ad" %>

<fmt:requestEncoding value="UTF-8" />

<c:remove var="userData" />

<jsp:useBean id="userData" class="ru.qwert21.labs.C9.User" scope="session" />

<jsp:setProperty name="userData" property="*" />

<ad:addUser user="${userData}" />

<c:choose>
    <c:when test="${sessionScope.errorMessage==null}">
        <%-- Ошибок не возникло, удалить из сессии сохранѐнные данные пользователя --%>
        <c:remove var="userData" scope="session" />
        <%-- Инициировать процесс аутентификации --%>
        <jsp:forward page="/doLogin.jsp" />
    </c:when>
    <c:otherwise>
        <%-- Переадресовать на форму регистрации --%>
        <c:redirect url="/register.jsp" />
    </c:otherwise>
</c:choose>