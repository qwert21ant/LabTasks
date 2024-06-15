clear
close all
clc

rng = [1 2];
M = 10000;

f = @(x) 1 ./ (x .* log(2));
F = @(x) integral(f, rng(1), x);

F_x = rng(1):((rng(2) - rng(1)) / M):rng(2);
F_y = arrayfun(F, F_x);

Z = arrayfun(@(~) unifrnd(0, 1), 1:M);

X = arrayfun(@(x) F_x(findApprox(F_y, x)), Z);
% ----------

%plot(F_x, F_y);
%plot(1:M, Z);

mean1 = sum(X) / length(X);
mean2 = mean(X);
mean3 = integral(@(x) x .* f(x), rng(1), rng(2));
disp(['Means: ' mat2str([mean1 mean2 mean3])]);

std1 = sqrt(sum(X.^2) / (length(X) - 1) - (sum(X))^2 / (length(X) * (length(X) - 1)));
std2 = sqrt(var(X));
std3 = sqrt(integral(@(x) (x - mean1).^2 .* f(x), rng(1), rng(2)));
disp(['Stds: ' mat2str([std1 std2 std3])]);

confD = norminv(1 - 0.05/2) * std3 / sqrt(M);
confInterval = [(mean1 - confD) (mean1 + confD)];
disp(['Conf interval: ' mat2str(confInterval)]);

h = hist(X, 100);
h = h ./ max(h);

plot_x = min(X):((max(X) - min(X)) / (100 - 1)):max(X);
pdf_t = f(plot_x);
pdf_e = h .* max(pdf_t) ./ max(h); 
plot(plot_x, pdf_t, 'r', plot_x, pdf_e, 'b');

figure

% plot_x = min(X):((max(X) - min(X)) / (M - 1)):max(X);
cdf_t = arrayfun(F, plot_x);
cdf_e = cumsum(pdf_t);
cdf_e = cdf_e ./ max(cdf_e);
plot(plot_x, cdf_t, 'r', plot_x, cdf_e, 'b');

% ----------
function res = findApprox(A, x)
  cur = 1000000;
  res = 0;
  for i = 1:length(A)
    if abs(A(i) - x) < cur
      cur = abs(A(i) - x);
      res = i;
    end
  end
end