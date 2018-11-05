clear
clc
y1_0 = 1;
y2_0 = 1;
y3_0 = -2;
[T,Y] = ode45(@(t,y)[-y(1)+y(2)-y(3)
                    -y(2)
                    0],[0 3],[y1_0 y2_0 y3_0]);
disp([T,Y(:,1),Y(:,2),Y(:,3)]);
hold on
plot(T,Y(:,1),'-r');
plot(T,Y(:,2),'-g');
plot(T,Y(:,3),'-b');
hold off
ylim([-3 3])
xlabel('t')
ylabel('x(t), y(t), z(t)')
grid on