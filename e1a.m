clear
clc
xlabel('Velocidad \Omega^2')
ylabel('Cambio en \alpha y \beta')
grid on
hold on
fplot('sin(x)',[-2*pi 2*pi -2 2],'-r')
fplot('cos(x)',[-2*pi 2*pi -2 2],'-g')
fplot('atan(x)/(sqrt(x.^2+1))',[-2*pi 2*pi -2 2],'-b')
hold off
grid on