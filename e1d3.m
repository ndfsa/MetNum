clear
clc
func = @(x,y)-3*x.^2+y.^2+6*x-8*y+17;
syms x y
f = -3*x.^2+y.^2+6*x-8*y+17;
fx = diff(f,x);
fy = diff(f,y);
syms off
xs = double(solve(fx,x));
ys = double(solve(fy,y));
hold on
plot3(xs,ys,func(xs,ys),'.r','markersize',20);
ezsurf(f, [-10 10 -10 10])
hold off
zlabel('z')
fprintf('saddle point at: x = %0.2f, y = %0.2f\n', xs, ys);
fprintf('value at saddle point: f(x,y) = %0.2f\n', func(xs,ys));