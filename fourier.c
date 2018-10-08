#include <stdio.h>
#include <math.h>
#include <memory.h>
#include <limits.h>
#include <stdlib.h>
/* * * * * * * * * * * * * * * * * * * *
* Series de Fourier en C-Linux         *
* Universidad: UPB                     *
* Autores: V. Loza, S. Marzana.        *
* Fecha: 2/10/2018                    *
* * * * * * * * * * * * * * * * * * * */
/*
* ESTE PROGRAMA APROXIMA UNA FUNCION EN UN PERIODO T
* CON UN LIMITE DE SUMATORIAS N.
*/
/////////////////INPUT//////////////////

#define N 10    +1//LIMITE DE LAS SUMATORIAS

#define T 8.0     // PERIODO EN EL QUE SE REALIZARA LA APROXIMACION
	          // ENTRE [0:T]

double f(double x) { return (x*x); }//FUNCION A APROXIMAR

/////////////////////////////////////////

double yr = 10;

double l = T / 2;

const double blocks = 20000.0;

double limit(double (*g)(double), double l);

double integrate(double k, double (*f)(double, double));

double fourier(double d, double *a, double *b);

double a; //limite inferior

double b; // limite superior
double pi;

double fcos(double x, double k) { return cos(k * pi * x / l); }

double fsin(double x, double k) { return sin(k * pi * x / l); }

int main(int argc, char *argv[]) {
    if(argc == 2){
    	yr = atof(argv[1]);
    }
    pi = 4 * atan(1);
    a = 0;
    b = 2 * l;
    double a[N];
    double b[N];
    a[0] = integrate(0, fcos) / (2 * l);
    b[0] = 0;
    for (int i = 1; i < N; ++i) {
        a[i] = integrate(i, fcos) / l;
        b[i] = integrate(i, fsin) / l;
        //printf("a: %0.8f  b: %0.8f\n", a[i], b[i]); //debug, valores de las integrales individuales
    }
    FILE *fp;
    fp = fopen("datos.dat","w");
    for (double i = 0.0; i < T; i+=0.01) {
        fprintf(fp,"%0.8f %0.8f %0.8f\n", i, fourier(i, a, b), f(i));
    }
    fclose(fp);
    /*for (double i = 0.0; i < 2 * l; i+=0.01) {
        printf("%0.8f %0.8f %0.8f\n", i, fourier(i, a, b), f(i)); //debug valores de los resultados
    }*/
	fp = fopen("fourier.gp","w");
	fprintf(fp, "reset \n"
		    "set nokey \n"
		    "set title \"Aproximacion con series de Fourier\" \n"
		    "set xlabel \"x\" \n"
		    "set ylabel \"y\" \n"
		    "set yrange[-%0.2f:%0.2f]\n"
		    "set grid \n"
		    "plot \"datos.dat\" u 1:2 with lines, \"datos.dat\" u 1:3 with lines \n"
		    "set size 0.7, 0.3 \n"
                    "set terminal postscript portrait enhanced 'Helvetica' 8 \n"
                    "set output 'figuraFourier.ps' \n"
                    "replot \n", yr, yr);
	fclose(fp);
    system("gnuplot -persist fourier.gp");
    return 0;
}

double fourier(double x, double *a, double *b) {
    double res = 0;
    for (double i = 0.0; i < N; ++i) {
        res += a[(int) i] * fcos(x,i) + b[(int) i] * fsin(x,i);
    }
    return res;
}

double integrate(double k, double (*g)(double, double)) {
    double res = (*g)(a, k) * limit(f, a);
    double h = (b - a) / blocks;
    for (int i = 1; i < blocks; i += 1) {
        res += 2 * (*g)(a + (((double) i) * h), k) * limit(f, (a + (((double) i) * h)));
    }
    res += (*g)(b, k) * limit(f, b);
    res *= h / 2;
    return res;
}

double limit(double (*g)(double), double lim) {
    if ((*g)(lim) == INFINITY || (*g)(lim) == -INFINITY || (*g)(lim) != (*g)(lim)) {
        return 0;
    } else {
        return (*g)(lim);
    }
}
