data = [
    1 1 2.75;
    2 2 2.77;
    3 2 2.6;
    4 2 2.42;
    5 2 2.26;
    6 2 2.12;
    8 2 1.78;
    10 2 1.45;
    12 2 1.12;
    14 2 0.8;
    
    2 4 2.38;
    3 3 2.61;
    3 4 2.65;
    4 4 2.47;
    5 4 2.32;
    6 4 2.16;
    7 3 1.94;
    8 4 1.79;
    10 4 1.42;
    12 4 1.11;
    14 4 0.7;
    
    1 6 3.28;
    3 6 2.75;
    5 6 2.36;
    7 6 1.97;
    8 6 1.79;
    9 6 1.62;
    10 6 1.4;
    12 6 1.05;
    14 6 0.57;
    
    2 8 2.95;
    4 8 2.51;
    6 8 2.13;
    8 8 1.79;
    10 8 1.32;
    12 8 1.03;
    14 8 0.58;
    
    2 10 2.8;
    4 10 2.46;
    6 10 2.11;
    8 10 1.77;
    10 10 1.42;
    12 10 1.04;
    14 10 0.68;
    
    4 11 2.47;
    10 12 1.46;
    12 12 1.08;
    14 12 0.77;
];

% X = [2 4 6 8 10 12 14];
% Y = [2 4 8 10];
% V = [
%     2.77 2.42 2.12 1.78 1.45 1.12 0.8;
%     2.38 2.47 2.16 1.79 1.42 1.11 0.7;
%     2.95 2.51 2.13 1.79 1.32 1.03 0.58;
%     2.8 2.46 2.11 1.77 1.42 1.04 0.68;
% ];


% [X, Y] = meshgrid(data(:, 1), data(:, 2));

% [X, Y, Z] = sphere;
% 
% surf(X, Y, Z);
% axis equal;

% scatter3

%interp2
% [X, Y] = meshgrid(0:17, 0:14);
% V = sin(X) + cos(Y);
% 
% [Xq, Yq] = meshgrid(1:0.5:17, 1:0.5:14);
% 
% Vres = interp2(X, Y, V, Xq, Yq, 'spline');
% 
% % surf(X, Y, V, 'EdgeColor', 'black')
% surf(Xq, Yq, Vres, 'EdgeColor', 'black')

plot(data(:, 1), data(:, 2), 'ro', 'MarkerSize', 4)
text(data(:, 1) + 0.1, data(:, 2) + 0.1, num2str(data(:, 3)), ...
    'VerticalAlignment', 'bottom', ...
    'HorizontalAlignment', 'left', ...
    'FontSize', 8)

% title('Значения потенциала в точках')
xlabel('x')
ylabel('y')
         
% xticks('manual')
% xticks([1 2 20])

ax = gca;
set(ax, 'XLim', [0 17]);
set(ax, 'YLim', [0 14]);

% clc
% clear all

% gca.DataAspectRatio = [1 1]