clear
clc
[T,Y] = ode45(@(t,y)[y(2);5*y(2)+14*y(1)],[0 1],[0 -(1/5)]);
plot(T,Y(:,1));
disp([T,Y(:,1)]);
xlabel('x')
ylabel('y')
grid on