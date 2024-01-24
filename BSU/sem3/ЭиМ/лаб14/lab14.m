data = [
  0.1 1.85
  0.15 2.516666667
  0.2 3.05
  0.25 3.516666667
  0.3 4.05
  0.35 4.65
  0.4 5.183333333
  0.45 5.85
  0.5 6.183333333
];

d = 0.36;

p = polyfit(data(:, 1), data(:, 2), 1);
disp(['tg = ', num2str(p(1))]);
disp(['p = ', num2str(pi * d * d / 4 * p(1))]);

figure(1);
plot(data(:, 1), data(:, 2), 'ro-', data(:, 1), polyval(p, data(:, 1)), 'r--');
xlabel('l, м');
ylabel('Rx, Ом');
title('Зависимость сопротивления провода от его длины');