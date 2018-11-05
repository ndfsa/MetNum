clear
clc
y0 = 5;
[x,y] = ode45(@(x,y)((x*y)/sqrt(x.^2-4)), [2.00001 3], y0);
plot(x,y);
disp([x,y])
%indeterminado para x = 2
%aproximacion para con x = 2.00001
grid on
xlabel('x')
ylabel('y')
