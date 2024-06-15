clear
close all
clc

iN = 101;

P = zeros(1, iN);
tmp = 1;

for i = 1:iN
  P(i) = 1 / (exp(1) * tmp);
  tmp = tmp * i;
end

M = 10000;
X = zeros(1, M);

i = 1;
while i <= M
  S = unifrnd(0, 1);

  j = 1;
  while S >= 0
    S = S - P(j);
    j = j + 1;
  end

  X(i) = (j - 1) - 1;
  i = i + 1;
end

% --------

mean_e = mean(X);
mean_t = sum((0:iN-1) .* P);

disp(['Mean: actual = ' num2str(mean_e) ', teor = ' num2str(mean_t)]);

% --------

std_e = std(X);
std_t = sum(((0:iN-1) - mean_t) .^ 2 .* P);

disp(['Std: actual = ' num2str(std_e) ', teor = ' num2str(std_t)]);

% --------

h = hist(X, max(X) + 1);

plot_x = min(X):max(X);
pdf_t = arrayfun(@(i) P(i+1), plot_x);
pdf_e = h / M; 
plot(plot_x, pdf_t, 'r', plot_x, pdf_e, 'b');

% --------

F = @(a, b) P(a+1);

r = max(X) - min(X) + 1;

p = arrayfun(@(i) F(i, i+1), min(X):max(X));

xi = sum((h - M .* p) .^ 2 ./ (M .* p));
xi_e = chi2inv(0.95, r - 1);

disp(['Xi: ' num2str(xi) ' < ' num2str(xi_e)]);

% --------
