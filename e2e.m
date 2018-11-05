clear
clc
y1_0 = 0;
y2_0 = 1;
[T,Y] = ode45(@(t,y)[5*y(1)+2*y(2)+3*t
    4*y(1)-7*y(2)+6*t],[0 0.5],[y1_0 y2_0]);
disp([T,Y(:,1),Y(:,2)]);
hold on
plot(T,Y(:,1),'-r');
plot(T,Y(:,2),'-b');
hold off
grid on
xlabel('t')
ylabel('x(t), y(t)')