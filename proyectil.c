#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>

/* * * * * * * * * * * * * * * * * * * *
* Lanzamiento de proyectil en C-Linux  *
* Universidad: UPB                     *
* Autores: V. Loza, S. Marzana.        *
* Fecha: 7/10/2018                    *
* * * * * * * * * * * * * * * * * * * */
/*
* ESTE PROGRAMA RECIBE 4 ARGUMENTOS: MASA, RESISTENCIA DEL AIRE, VELOCIDAD INICIAL
* Y DISTANCIA A ALCANZAR, COMO: m b v0 dist.
* EL RESULTADO ES LA GRAFICA DE LA TRAYECTORIA DEL PROYECTIL, MAS EL ANGULO DE
* DISPARO Y EL TIEMPO DE VUELO.
*/
/////////////////////////////INPUT/////////////////////////////////////
/* POR FAVOR NOTESE QUE SE DEBE COMENTAR EL BLOQUE DE INPUT CON
 * ARGUMENTOS QUE SE INDICA ABAJO PARA ASIGNAR MANUALMENTE LAS
 * VARIABLES EN ESTA SECCION
 */
double m; //MASA DEL PROYECTIL

double b; //RESISTENCIA DEL AIRE

double v0; //VELOCIDAD INICIAL DEL PROYECTIL

double dist; //DISTANCIA A ALCANZAR

/////////////////////////////////////////////////////////////////////

double h = 0.001;

void nextStep(double *res, double (*f)(double, double, double),
              double (*g)(double, double, double));

double fx(double t, double x, double v);

double gx(double t, double x, double v);

double fy(double t, double y, double v);

double gy(double t, double y, double v);


int main(int argc, char *argv[]) {
////////////////////BLOQUE DE INPUT CON ARGUMENTOS/////////////////////
    if (argc != 5) {
        printf("Program expects 4 arguments, received: %d\n", argc - 1);
        return 1;
    }
    m = atof(argv[1]);
    b = atof(argv[2]);
    v0 = atof(argv[3]);
    dist = atof(argv[4]);
///////////////////////////////////////////////////////////////////////

/////////////////////VARIABLES VARIAS//////////////////////////////////

    double step = 0.01; // PASO INICIAL DE LA BUSQUEDA DE ANGULO
    double t = 0; // TIEMPO INICIAL
    double xInit = 0; //POSICION INICIAL EN X
    double yInit = 0; //POSICION INICIAL EN Y
    double error = 0.001; //ERROR ACEPTABLE AL ENCONTRAR EL RESULTADO
    double angle = 4 * atan(1) / 2; //ANGULO INICIAL DE BUSQUEDA
    double fl = 0; // NIVEL DEL PISO

    double xPos[3] = {t, xInit, v0 * cos(angle)};
    double yPos[3] = {t, yInit, v0 * sin(angle)};
    double yMin = INT_MAX;
    double yMax = 0;
    double xMax = 0;
    double fTime = 0;
    int flag = 0;
    int solution = 0;
    FILE *fp;

    while (angle > 0.0) {
        fp = fopen("datos.dat", "w");
        fprintf(fp, "%0.6f %0.6f %0.6f\n", xPos[1], yPos[1], xPos[0]);
        do {
            nextStep(xPos, fx, gx);
            nextStep(yPos, fy, gy);
            fprintf(fp, "%0.6f %0.6f %0.6f\n", xPos[1], yPos[1], xPos[0]);
            if (yPos[1] >= 0 && yPos[1] < yMin) {
                yMin = yPos[1];
                xMax = xPos[1];
                fTime = yPos[0];
            }
            if (yPos[1] >= yMax) {
                yMax = yPos[1];
            }
        } while (yPos[1] >= fl);
        fclose(fp);
        if (fabs(xMax - dist) / dist * 100 <= error) {
            printf("angle: %0.8f time: %0.3f\n", angle, fTime);
            solution = 1;
            break;
        }
        if ((flag == 0) && (xMax >= dist)) {
            step *= -0.5;
            flag = 1;
        }
        if ((flag == 1) && (xMax <= dist)) {
            step *= -0.5;
            flag = 0;
        }
        angle -= step;
        xPos[0] = t;
        xPos[1] = xInit;
        xPos[2] = v0 * cos(angle);

        yPos[0] = t;
        yPos[1] = yInit;
        yPos[2] = v0 * sin(angle);

        yMin = INT_MAX;
        xMax = 0;
        fTime = 0;
        yMax = 0;
    }
    if (!solution) {
        printf("Could not find a solution with parameters.\n");
    } else {
        fp = fopen("proyectil.gp", "w");
        fprintf(fp, "reset \n"
		    "set nokey \n"
		    "set title \"Trayectoria del proyectil\" \n"
                    "set xlabel \"x\" \n"
                    "set ylabel \"y\" \n"
                    "set xrange[%0.2f:%0.2f] \n"
                    "set yrange[%0.2f:%0.2f] \n"
                    "set grid \n"
                    "plot \"datos.dat\" u 1:2 with lines \n"
                    "set size 0.7, 0.3 \n"
                    "set terminal postscript portrait enhanced 'Helvetica' 8 \n"
                    "set output 'figuraProyectil.ps' \n"
                    "replot \n",
                xInit, dist + (dist / 10),
                yInit, yMax + (yMax / 10));
        fclose(fp);
        system("gnuplot -persist proyectil.gp");
    }
    return 0;
}

void nextStep(double *res, double (*f)(double, double, double),
              double (*g)(double, double, double)) {
    double kn;
    double ln;
    double funcAcc = 0;
    double vAcc = 0;
    kn = h * f(res[0], res[1], res[2]);
    ln = h * g(res[0], res[1], res[2]);

    funcAcc += kn;
    vAcc += ln;

    kn = h * f(res[0] + (h / 2), res[1] + (kn / 2), res[2] + (ln / 2));
    ln = h * g(res[0] + (h / 2), res[1] + (kn / 2), res[2] + (ln / 2));

    funcAcc += 2 * kn;
    vAcc += 2 * ln;

    kn = h * f(res[0] + (h / 2), res[1] + (kn / 2), res[2] + (ln / 2));
    ln = h * g(res[0] + (h / 2), res[1] + (kn / 2), res[2] + (ln / 2));

    funcAcc += 2 * kn;
    vAcc += 2 * ln;

    kn = h * f(res[0] + h, res[1] + kn, res[2] + ln);
    ln = h * g(res[0] + h, res[1] + kn, res[2] + ln);

    funcAcc += kn;
    vAcc += ln;

    funcAcc /= 6.0;
    vAcc /= 6.0;

    res[0] += h;
    res[1] += funcAcc;
    res[2] += vAcc;
}

double fx(double t, double x, double v) { return v; };

double gx(double t, double x, double v) { return -b * v / m; };

double fy(double t, double y, double v) { return v; };

double gy(double t, double y, double v) { return -b * v / m - 9.81; };

