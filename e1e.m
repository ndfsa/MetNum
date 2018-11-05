clear
clc
func = @(x,y)x.*y*log(x.^2+y.^2);
syms x y
f = x.*y*log(x.^2+y.^2);
f1 = diff(f,x);
f2 = diff(f,y);
s=solve(f1,f2);
hold on
ezsurf(f, [-10 10 -10 10])
plot3(s.x,s.y, func(s.x,s.y),'.r','markersize',20)
hold off
zlabel('z')
fprintf('saddle point at: x = %0.2f, y = %0.2f\n', double(s.x), double(s.y));
fprintf('value at saddle point: f(x,y) = %0.2f\n', double(func(s.x,s.y)));