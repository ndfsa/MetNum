clear
clc
y1_0 = 0;
y2_0 = 0;
[T,Y] = ode45(@(t,y)[-exp(t)-3*y(2)+cos(t)
                    2*exp(t)+4*y(2)-cos(t)],[0 2*pi],[y1_0 y2_0]);
disp(T)
disp([Y(:,1),Y(:,2)]);
hold on
plot(T,Y(:,1),'-r')
plot(T,Y(:,2),'-b')
hold off
xlim([0 2*pi])
xlabel('t')
ylabel('x(t), y(t)')
grid on