//Romina Gomez Hugo Yepez
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 10

typedef struct
{
    int id;
    char titulo[100];
    char autor[50];
    int year;
    char estado[12];
} Libro;

Libro v[MAX];
int n = 0;

int idx(int id)
{
    for (int i = 0; i < n; i++)
        if (v[i].id == id)
            return i;
    return -1;
}

int LeerEnteroPositivo(const char *msg)
{
    char buf[32];
    do
    {
        printf("%s", msg);
        if (!fgets(buf, sizeof(buf), stdin))
            continue;
        if (strchr(buf, '.') || strchr(buf, ','))
        {
            puts(" -No Se Permiten Decimales...Intenta Nuevamente- ");
            continue;
        }
        int num;
        if (sscanf(buf, "%d", &num) == 1 && num >= 1)
            return num;
        puts(" -No Se Pueden Agregar Letras Ni Numeros Negativos...Intenta Nuevamente- ");
    } while (1);
}

void LeerTexto(const char *msg, char *dts, int max)
{
    char temp[256];
    int len;
    do
    {
        printf("%s", msg);
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';
        len = strlen(temp);
        if (len >= max)
        {
            printf(" -Demasiado Largo(MAX 99)...Intenta Nuevamente\n- ");
        }
    } while (len >= max);
    strcpy(dts, temp);
}

void LeerAutor(const char *msg, char *dst, int max)
{
    char temp[256];
    int len;
    int TieneNumero;
    do
    {
        printf("%s", msg);
        fgets(temp, sizeof(temp), stdin);
        temp[strcspn(temp, "\n")] = '\0';
        len = strlen(temp);
        TieneNumero = 0;
        for (int i = 0; temp[i]; i++)
            if (isdigit(temp[i]))
            {
                TieneNumero = 1;
                break;
            }
        if (TieneNumero || len >= max)
            printf(" -No Se Permiten Numeros y No debes exceder el max de caracteres(49)- \n", max - 1);
    } while (TieneNumero || len >= max);
    strcpy(dst, temp);
}
