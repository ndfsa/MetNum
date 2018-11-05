clear
clc
func = @(x,y)-71+12*x+32*y-3*x.^2-4*y.^2;
func2 = @(x,y)-func(x,y);
max = fminsearch(@(v)func2(v(1),v(2)),[10 10]);
fprintf('max at: x = %0.2f, y = %0.2f\n', max(1), max(2))
value = func(max(1), max(2));
fprintf('value at max: f(x, y) = %0.2f\n', value)
ezsurf(func, [-4 10 -4 10])
zlabel('z')