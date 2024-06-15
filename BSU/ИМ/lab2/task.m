M = 8500;
K = 10;

mu = -10;
sigma = 0.5;

lambda = 9.5;

prec = 4;

clc;
close all;

disp('--- Normal distribution ---');

x_distr = randn(1, M) * sigma + mu;

disp(['First values: ' mat2str(x_distr(1:K), prec)]);
disp(['Range: ' num2str(min(x_distr), prec) ' ' num2str(max(x_distr), prec)]);
disp(['Mean: theory = ' num2str(mu, prec) ' actual = ' num2str(mean(x_distr), prec)]);
disp(['Std: theory = ' num2str(sigma, prec) ' actual = ' num2str(std(x_distr), prec)]);

L = [32 316 1000 3162 M];
means = arrayfun(@(x) mean(x_distr(1:L(x))), 1:length(L));

figure;
plot(log(L) ./ log(10), means);
yline(mu);

figure;
hold on;

h = hist(x_distr, 100);
hist(x_distr, 100);

x = min(x_distr):0.01:max(x_distr);
p = normpdf(x, mu, sigma);
plot(x, p * max(h) / max(p), 'r');

figure;
F = cumsum(p) / 100;
Ft = normcdf(x, mu, sigma);
plot(x, F, 'r', x, Ft, 'b');

disp('--- Normal distribution ---');

x_distr = poissrnd(lambda, 1, M);

disp(['First values: ' mat2str(x_distr(1:K), prec)]);
disp(['Range: ' num2str(min(x_distr), prec) ' ' num2str(max(x_distr), prec)]);
disp(['Mean: theory = ' num2str(lambda, prec) ' actual = ' num2str(mean(x_distr), prec)]);
disp(['Std: theory = ' num2str(sqrt(lambda), prec) ' actual = ' num2str(std(x_distr), prec)]);

figure;
hold on;

h = hist(x_distr, max(x_distr) - min(x_distr) + 1);
hist(x_distr, max(x_distr) - min(x_distr) + 1);

x = min(x_distr):max(x_distr);
p = poisspdf(x, lambda);
plot(x, p * max(h) / max(p), 'r');