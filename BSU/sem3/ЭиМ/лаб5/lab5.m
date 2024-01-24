data = [
  25 1.44 0.166 147
  35 0.96 0.17 94
  46 0.7 0.173 73
  56 0.55 0.178 50
  66 0.43 0.182 38
  76 0.33 0.189 29
  86 0.254 0.196 22
  96 0.19 0.2 16.7
];

graph1(1, data(:,1), data(:,2));
graph1(2, data(:,1), data(:,3));
graph1(3, data(:,1), data(:,4));

graph3(1, data(:,1), data(:,2));
graph2(2, data(:,1), data(:,3));
graph3(3, data(:,1), data(:,4));

function [] = graph1(n, x, y)
  f = figure(n);
  plot(x, y, 'ro-');
  title(['Зависимость сопротивления от температуры ', num2str(n), 'го образца']);
  xlabel('t, ºC');
  ylabel('R, кОМ');
  saveas(f, ['graph1-', num2str(n), '.png']);
end

function [] = graph2(n, x, y)
  p = polyfit(x, y, 1);
  disp(['Alpha coeff for ', num2str(n), ' material: ', num2str(p(1)./p(2))]);

  f = figure(10 + n);
  plot(x, y, 'ro-', x, polyval(p, x), 'r--');
  title(['Зависимость сопротивления от температуры ', num2str(n), 'го образца']);
  xlabel('t, ºC');
  ylabel('R, кОМ');
  saveas(f, ['graph2-', num2str(n), '.png']);
end

function [] = graph3(n, x, y)
  newX = 1 ./ (x + 273);
  newY = log(1 ./ y);
  
  p = polyfit(newX, newY, 1);
  disp(['delta E for ', num2str(n), ' material: ', num2str(-2 * (1.380649e-23) * p(1))]);

  f = figure(10 + n);
  plot(newX, newY, 'ro-', newX, polyval(p, newX), 'r--');
  title(['Зависимость ln(1/R) от 1/T ', num2str(n), 'го образца']);
  xlabel('1/T, 1/К');
  ylabel('ln(1/R)');
  saveas(f, ['graph3-', num2str(n), '.png']);
end