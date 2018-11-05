clear
clc
func = @(x,y)x.^2+2*y.^2-2*x-8*y+12;
min = fminsearch(@(v)func(v(1),v(2)),[10 10]);
fprintf('min at: x = %0.2f, y = %0.2f\n', min(1), min(2));
value = func(min(1), min(2));
fprintf('value at min: f(x, y) = %0.2f\n', value);
ezsurf(func, [-3 3 -1.5 3]);
zlabel('z')