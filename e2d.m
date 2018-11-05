clear
clc
[T,Y] = ode45(@(t,y)[y(2);-9*y(1)],[0 pi],[pi 2*pi]);
plot(T,Y(:,1));
disp([T,Y(:,1)]);
xlim([0 pi])
xlabel('x')
ylabel('y')
grid on