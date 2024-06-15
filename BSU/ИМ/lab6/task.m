clear
close all
clc

M = 10000;
N = 100;

rng = [0 1];
lambda = 0.5;

F = arrayfun(@(~) gen_flow(rng, lambda), zeros(M, 1), 'UniformOutput', false);

% -------

plot_x = rng(1):((rng(2) - rng(1)) / N):rng(2);

H = cell2mat(arrayfun(@(flow) hist(cell2mat(flow), plot_x), F, 'UniformOutput', false));
h = arrayfun(@(i) sum(H(:, i + 1)), 0:N);

lambda_t = arrayfun(@(~) lambda, plot_x);
lambda_e = h ./ ((rng(2) - rng(1)) / N) ./ M;
plot(plot_x, lambda_t, 'r', plot_x, lambda_e, 'b');

mean_l_e = mean(lambda_e);
mean_l_t = mean(lambda_t);

disp(['Mean lambda: actual = ' num2str(mean_l_e) ', teor = ' num2str(mean_l_t)]);

% -------

figure
hold on;

n = arrayfun(@(flow) length(cell2mat(flow)), F);

plot_x = 0:max(n);

h = hist(n, plot_x);
plot(plot_x, h ./ M, 'b');

p_t = arrayfun(@(i) poisspdf(i, lambda * (rng(2) - rng(1))), plot_x);
plot(plot_x, p_t, 'r');

% -------

function flow = gen_flow(rng, lambda)
  flow = [];

  z = unifrnd(0, 1);
  t = rng(1) - log(z) / lambda;
  
  while t <= rng(2)
    flow = [flow t];
  
    z = unifrnd(0, 1);
    t = t - log(z) / lambda;
  end
end