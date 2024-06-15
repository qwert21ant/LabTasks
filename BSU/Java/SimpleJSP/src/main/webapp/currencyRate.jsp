<%@ taglib prefix="fmt" uri="http://java.sun.com/jsp/jstl/fmt" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head>
  <title>Currency Rates</title>
  <link rel="stylesheet" type="text/css" href="css/styles.css">
</head>
<body>
  <jsp:useBean id="rate" scope="request" type="com.example.simplejsp.CurrencyRate"/>
  <h1>Current Currency Rates</h1>
  <h3>Base currency: <c:out value="${rate.base}" /></h3>
  <table>
    <tr>
      <th>Currency</th>
      <th>Rate</th>
    </tr>
    <c:forEach var="entry" items="${rate.rates}">
      <tr>
        <td><c:out value="${entry.key}" /></td>
        <td><fmt:formatNumber value="${entry.value}" type="number" minFractionDigits="2" maxFractionDigits="4" /></td>
      </tr>
    </c:forEach>
  </table>
</body>
</html>