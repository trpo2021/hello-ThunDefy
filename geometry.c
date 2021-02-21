#include <ctype.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fl = 1;
int Ax1 = 0, Ay1 = 0, Ax2 = 0, Ay2 = 0, Bx1 = 0, By1 = 0, Bx2 = 0, By2 = 0;
double Aper = 0, Aarea = 0, Bper = 0, Barea = 0;
const double pi = 3.1415926535;

int circle(int x, int y, float r)
{ // Функция пока не используется и работает только для 2х окружностей.

    if (fl == 1) {
        Ax1 = x + r;
        Ay1 = y + r;
        Ax2 = x - r;
        Ay2 = y - r;

        Aper = 2 * pi * r;
        Aarea = pi * (r * r);
    }
    if (fl == 2) {
        Bx1 = x + r;
        By1 = y + r;
        Bx2 = x - r;
        By2 = y - r;

        Bper = 2 * pi * r;
        Barea = pi * (r * r);

        printf("\nПериметр окружности А = %2.4f", Aper);
        printf("\nПлощадь окружности А = %2.4f\n", Aarea);

        printf("\nПериметр окружности B = %2.4f", Bper);
        printf("\nПлощадь окружности B = %2.4f\n", Barea);

        if (Ax1 > Bx2 && Ax2 < Bx1 && Ay1 > By2 && Ay2 < By1)
            printf("\n~Окружности пересекаются~\n");
        else
            printf("~Пересечений нет~\n");
    }
    fl++;
}

char* strlwr(char* str) // Функция которая переводит все буквы в нижний регистр
{
    unsigned char* p = (unsigned char*)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

int main()
{
    char letter[]
            = "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm~!@#№$;%%^:"
              "&?*-=+_}{|)(?><\"\'";
    int fin = 2, // Из за ошибки которая описана ниже, вводить количество фигур придется здесь 
        repeat; 


     //printf("How many circles?: "); // Выбор - сколько фигур будет вводиться
     //fin = scanf("%d", &fin); // Из за ошибки: "Ошибка сегментирования (стек памяти сброшен на диск)", я временно отключил эту возможность до фикса.    
     //if (fin == 0) {
     //printf("You can only enter integer.\n");
     //return 0;
     //}

    printf("\nEnter the point X , point Y and radius for each "
           "circle.\nFor example: circle(0 0, 1.5)\n");

    for (repeat = 1; repeat <= fin; repeat++) {
        char input[80];
        int fin = 0, repeat = 0, i, j, j2, in = 1, end = 0,
            fl1 = 0, com = 0, err1 = 0, err2 = 0, err3 = 0, err4 = 0,
            err6 = 1, XtoY = 0;
        char *cmd, *chX, *chY, *chR;
        int x = 0, y = 0;

        printf("\n~~~\n");

        gets(input);

        cmd = malloc(1);
        strcpy(cmd, input);
        cmd = strtok(cmd, "(");
        cmd = strtok(cmd, " ");
        strlwr(cmd);

        if (strcmp(cmd, "circle") != 0) {
            printf("expected 'circle' not a '%s'\n", cmd);
            return 0;
        }

        for (i = 0; input[i] != '\0'; i++) {
            if (input[i] == '(')
                fl1 = 1;
            end++;
        }

        if (fl1 == 0) {
            printf("Error: expected '('\n");
            err1 = 1;
        }

        if (fl1 == 1) {
            if (input[end - 1] != ')') {
                printf("Error at column %d: expected ')'\n", end);
                err2 = 1;
            }

            for (i = 0; input[i] != '('; i++)
                in++;

            for (i = in; input[i] != ')'; i++) {
                if (input[i] == ',')
                    err6 = 0;
            }
            if (err6 == 1) {
                printf("Error: expected ','\n");
                return 0;
            }

            for (; in != end - 1; in++) { // Проверки в скобках (  )
                for (j = 0; j < sizeof(letter) - 1; j++) {
                    if (input[in] == letter[j]) {
                        printf("Error at column %d expected '<integer>' or "
                               "'<double>' , now '%c'\n",
                               in,
                               input[in]);
                        err3 = 1;
                    }
                }

                if (input[in] == ',') {
                    com++;
                    if (com > 1) {
                        printf("Error at column %d extra ','\n", in);
                        err4 = 1;
                    }
                }
            }
        }

        if (err1 == 0 && err2 == 0 && err3 == 0 && err4 == 0 && err6 == 0) {
            for (i = 0, in = 0; input[i] != '('; i++)
                in++;
            chX = malloc(1);
            chY = malloc(1);
            in++;
            for (j = 0, j2 = 0; input[in] != ','; in++) {
                if (XtoY == 0) {
                    chX[j] = input[in];
                    j++;
                    if (atoi(chX) != 0 && input[in] == ' ')
                        XtoY = 1;
                }
                if (XtoY == 1) {
                    chY[j2] = input[in];
                    j2++;
                    if (atoi(chX) != 0 && atoi(chY) != 0 && input[in] == ' ') {
                        for (i = in; input[i] != ','; i++) {
                            if (input[i] != ' ') {
                                printf("Error at column %d: unexpected token\n",
                                       i);
                                return 0;
                            }
                        }
                    }
                }
            }

            chR = malloc(10);
            for (j = 0, in++; input[in] != ')'; in++) {
                chR[j] = input[in];
                j++;

                if (atof(chR) != 0 && input[in] == ' ') {
                    for (i = in; input[i] != ')'; i++) {
                        if (input[i] != ' ') {
                            printf("Error at column %d: unexpected token\n", i);
                            return 0;
                        }
                    }
                }
            }

            x = atoi(chX);
            y = atoi(chY);
            double r = (double)atof(chR);

            printf("\nCmd = %s\n", cmd);
            printf("\nX = %d\n", x);
            printf("Y = %d\n", y);
            printf("R = %5.3lf\n", r);

        } else
            return 0;

        chX = NULL;

        chY = NULL;

        chR = NULL;
    }
}
