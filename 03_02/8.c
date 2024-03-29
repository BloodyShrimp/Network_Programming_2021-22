#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define B_SIZE 1024 // rozmiar tablicy

char buffer; // globalna tablica znaków o rozmiarze B_SIZE bajtów

int main(int argc, const char *argv[])
{
    if (argc != 3) // obsługa błędu przy złej liczbie argumentów
    {
        printf("Nieprawidłowa liczba argumentów.\nPrawidłowe użycie programu %s wygląda następująco: \n%s nazwa_pliku_źródłowego nazwa_pliku_docelowego\n", argv[0], argv[0]);
        exit(EXIT_FAILURE);
    }

    int read_bytes = 0; // zmienne odczytanych i zapisanych bajtów
    int written_bytes = 0;
    const char *source = argv[1]; // zmienne nazw pliku źrodłowego i docelowego
    const char *target = argv[2];
    int sourcedesc = open(source, O_RDONLY);                    // otwarcie pliku źródłowego i docelowego oraz zmienne zawierające ich deskryptory
    int targetdesc = open(target, O_WRONLY | O_CREAT, S_IRWXU); // jeżel plik docelowy nie istnieje to zostanie stworzony
    int line_count = 1;
    int delimiter = 0;

    if (sourcedesc == -1) // obsługa błędu otwarcia pliku źródłowego
    {
        perror("Błąd otwarcia pliku źródłowego");
        exit(EXIT_FAILURE);
    }
    if (targetdesc == -1) // obsługa błędu otwarcia pliku docelowego
    {
        perror("Błąd otwarcia pliku docelowego");
        exit(EXIT_FAILURE);
    }
    while ((read_bytes = read(sourcedesc, &buffer, 1)) != 0) // pętla odczytująca bajty z pliku źródłowego póki odczytano więcej niż 0 bajtów
    {
        if (read_bytes == -1) // obsługa błędu funkcji read()
        {
            perror("Błąd odczytu");
            exit(EXIT_FAILURE);
        }
        if (buffer == '\n' && delimiter == 1)
        {
            line_count++;
            delimiter = 0;
        }
        else if (buffer == '\n')
        {
            line_count++;
        }
        else if (buffer == '\r')
        {
            delimiter = 1;
        }
        if (line_count % 2 == 1 && delimiter == 0)
        {
            written_bytes = write(targetdesc, &buffer, read_bytes); // zapisanie odczytanych bajtów do pliku docelowego
            if (written_bytes == -1)                                // obsługa błędu funkcji write()
            {
                perror("Błąd zapisu");
                exit(EXIT_FAILURE);
            }
        }
    }
    if (close(sourcedesc) == -1) // zamknięcie pliku źródłowego i obsługa błędu
    {
        perror("Błąd zamknięcia pliku źrodłowego");
        exit(EXIT_FAILURE);
    }
    if (close(targetdesc) == -1) // zamknięcie pliku docelowego i obsługa błędu
    {
        perror("Bład zamknięcia pliku docelowego");
        exit(EXIT_FAILURE);
    }
}