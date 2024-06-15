clear
close all
clc

rng = [0 pi/2];
M = 10000;

f = @(x) cos(x);
g = @(~) 1;

X = zeros(1, M);
i = 1;

while i <= M
  a = unifrnd(rng(1), rng(2));
  b = unifrnd(0, g(a));

  if (b < f(a))
    X(i) = a;
    i = i + 1;
  end
end

% --------

h = hist(X, 100);

plot_x = min(X):((max(X) - min(X)) / (100 - 1)):max(X);
pdf_t = f(plot_x);
pdf_e = h .* max(pdf_t) ./ max(h); 
plot(plot_x, pdf_t, 'r', plot_x, pdf_e, 'b');

% --------

F = @(a, b) integral(f, a, b);

r = 100;
m = rng(1):((rng(2) - rng(1)) / r):rng(2);

p = arrayfun(@(i) F(m(i), m(i+1)), 1:100);

xi = sum((h - M .* p) .^ 2 ./ (M .* p));
xi_e = chi2inv(0.95, r - 1);

disp(['Xi: ' num2str(xi) ' < ' num2str(xi_e)]);

% --------

Q = sort(X);

w = 1 / (12 * M) + sum(arrayfun(@(i) F(rng(1), Q(i)) - (i - 0.5) ./ M, 1:M) .^ 2);
w_e = 0.46;

disp(['W: ' num2str(w) ' < ' num2str(w_e)]);

% --------