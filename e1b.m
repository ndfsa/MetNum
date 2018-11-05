clear
clc
func = @(x)sin(2.*x)./(x.^2.+pi.^2);
res = integral(func, -pi, 3*pi);
fprintf('Answer = %0.5f\n', res);