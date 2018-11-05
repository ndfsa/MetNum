clear
clc
[t,y] = ode45(@(y,t)2*y - 4, [3 1], 2);
plot(t,y);
xlabel('x')
ylabel('y')
disp(flipud([t,y]))
grid on
