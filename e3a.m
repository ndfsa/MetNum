clear
clc
y1_0 = 1;
y2_0 = 2;
y3_0 = 1;
y4_0 = 0;
[T,Y] = ode45(@(t,y)[y(2)
                    y(3)
                    y(4)
                    y(1)],[0 pi],[y1_0 y2_0 y3_0 y4_0]);
disp([T,Y(:,1),Y(:,3)]);
hold on
plot(T,Y(:,1),'-r')
plot(T,Y(:,3),'-b')
hold off
xlim([0 pi])
xlabel('t')
ylabel('x(t), y(t)')
grid on