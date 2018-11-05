clear
clc
func = @(x)4*x-x.^2;
max = fminsearch(@(x)-func(x),10);
value = func(max);
fprintf('max at: x = %0.2f\n', max);
fprintf('value at max: f(x) = %0.2f\n', func(max));
fplot(func, [-2 6 -5 5])
grid on
xlabel('x')
ylabel('y')