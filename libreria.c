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
void Alta_Libro()
{
    if (n == MAX)
    {
        puts(" -La Libreria Esta Llena...Prueba Borrando Un Libro- ");
        return;
    }
    int id = LeerEnteroPositivo("ID: ");
    if (idx(id) >= 0)
    {
        puts(" -ID Repetido...Prueba Ingresando Otro ID- ");
        return;
    }
    v[n].id = id;
    LeerTexto("TITULO: ", v[n].titulo, 100);
    LeerAutor("AUTOR: ", v[n].autor, 50);
    v[n].year = LeerEnteroPositivo("YEAR: ");
    strcpy(v[n].estado, "Disponible");
    n++;
}

void Lista_Libros()
{
    if (!n)
    {
        puts(" -La Lista Esta Vacia...Prueba Dando De Alta Un Libro- ");
        return;
    }
    printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "TITULO", "AUTOR", "YEAR", "ESTADO");
    for (int i = 0; i < n; i++)
        printf("%-5d %-30s %-20s %-6d %-12s \n", v[i].id, v[i].titulo, v[i].autor, v[i].year, v[i].estado);
}

void Buscar_Libros()
{
    int op;
    printf(" -Buscar Libro- \n");
    printf("1) ID \n");
    printf("2) NOMBRE \n");
    printf("OPCION: ");
    scanf("%d", &op);
    getchar();
    if (op == 1)
    {
        int id = LeerEnteroPositivo("ID: ");
        int i = idx(id);
        if (i < 0)
        {
            puts(" -El ID que ingresaste no coincide con ningun libro- ");
            return;
        }
        printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "TITULO", "AUTOR", "YEAR", "ESTADO");
        printf("%-5d %-30s %-20s %-6d %-12s \n", v[i].id, v[i].titulo, v[i].autor, v[i].year, v[i].estado);
    }
    else
    {
        char nombre[100];
        LeerTexto("NOMBRE: ", nombre, 100);
        int found = 0;
        printf("\n%-5s %-30s %-20s %-6s %-12s\n", "ID", "TITULO", "AUTOR", "YEAR", "ESTADO");
        for (int i = 0; i < n; i++)
        {
            if (strstr(v[i].titulo, nombre))
            {
                printf("%-5d %-30s %-20s %-6d %-12s\n", v[i].id, v[i].titulo, v[i].autor, v[i].year, v[i].estado);
                found = 1;
            }
        }
        if (!found)
            puts(" -EL Nombre Que Ingresaste No Coincide Con Ningun Libro- ");
    }
}

void Cambiar_Estado()
{
    int id = LeerEnteroPositivo("ID: ");
    int i = idx(id);
    if (i < 0)
    {
        puts(" -El ID que ingresaste no coincide con ningun libro- ");
        return;
    }
    if (strcmp(v[i].estado, "Disponible") == 0)
    {
        strcpy(v[i].estado, "Prestado");
        puts("Libro prestado exitosamente");
    }
    else
    {
        strcpy(v[i].estado, "Disponible");
        puts("Libro devuelto...Ahora esta Disponible");
    }
}

void Borrar_Libros()
{
    int id = LeerEnteroPositivo("ID: ");
    int i = idx(id);
    if (i < 0)
    {
        puts(" -El ID que ingresaste no coincide con ningun libro- ");
        return;
    }
    for (int j = i; j < n - 1; j++)
        v[j] = v[j + 1];
    n--;
    puts(" -Libro borrado exitosamente- ");
}
