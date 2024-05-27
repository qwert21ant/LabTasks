<%@page language="java" pageEncoding="UTF-8" %>
<%@taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@taglib prefix="ad" uri="http://ru.qwert21.labs.C9.tags/ad" %>

<fmt:requestEncoding value="UTF-8" />

<c:remove var="adData" />

<c:choose>
    <%-- Если параметр id больше нуля (т.е. модифицируется существующее
    объявление) --%>
    <c:when test="${param.id>0}">
        <%-- то сначала извлечь его --%>
        <ad:getAds id="${param.id}" var="ad" />
        <%-- и переместить из page в session --%>
        <c:set var="adData" scope="session" value="${ad}"/>
    </c:when>
    <c:otherwise>
        <%-- В противном случае создать новое объявление в области
        видимости сессии --%>
        <jsp:useBean id="adData" class="ru.qwert21.labs.C9.Ad" scope="session" />
    </c:otherwise>
</c:choose>

<jsp:setProperty name="adData" property="subject" />
<jsp:setProperty name="adData" property="body" />

<ad:updateAd ad="${adData}"/>

<c:choose>
    <c:when test="${sessionScope.errorMessage==null}">
        <%-- Ошибок не возникло, очистить временные данные --%>
        <c:remove var="adData" scope="session" />
        <%-- Переадресовать на страницу личного кабинета --%>
        <c:redirect url="/cabinet.jsp" />
    </c:when>
    <c:otherwise>
        <%-- Переадресовать на страницу редактирования объявления --%>
        <c:redirect url="/updateAd.jsp">
        <%-- В качестве параметра при переадресации передать id
        объявления --%>
        <c:param name="id" value="${adData.id}" />
        </c:redirect>
    </c:otherwise>
</c:choose>