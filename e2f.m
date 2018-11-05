clear
clc
y1_0 = 1;
y2_0 = 0;
y3_0 = 0;
%primera parte del grafico
[T1,Y1] = ode45(@(t,y)[3*y(1)-2*y(2)+2*y(3)
                    -2*y(1)+3*y(2)-2*y(3)
                    2*y(1)-2*y(2)+3*y(3)],[0 -0.5],[y1_0 y2_0 y3_0]);
%segunda parte del grafico
[T2,Y2] = ode45(@(t,y)[3*y(1)-2*y(2)+2*y(3)
                    -2*y(1)+3*y(2)-2*y(3)
                    2*y(1)-2*y(2)+3*y(3)],[0 0.1],[y1_0 y2_0 y3_0]);
disp(flipud([T1,Y1(:,1),Y1(:,2),Y1(:,3)]));
disp([T2,Y2(:,1),Y2(:,2),Y2(:,3)]);
hold on
plot(T1,Y1(:,1),'-r');
plot(T2,Y2(:,1),'-r');
plot(T1,Y1(:,2),'-g');
plot(T2,Y2(:,2),'-g');
plot(T1,Y1(:,3),'-b');
plot(T2,Y2(:,3),'-b');
hold off
grid on
xlabel('t')
ylabel('x(t), y(t), z(t)')