#include <stdio.h>
#include <stdlib.h>

int main()
{
    int liczby[50];
    int liczba;
    int i = 0;
    while (scanf("%d", &liczba) != EOF)
    {
        if (liczba == 0 || i == 50)
        {
            break;
        }
        *(liczby + i) = liczba;
        i++;
    }

    for (int j = 0; j < i; j++)
    {
        if (*(liczby + j) > 10 && *(liczby + j) < 100)
        {
            printf("%d\n", *(liczby + j));
        }
    }
}