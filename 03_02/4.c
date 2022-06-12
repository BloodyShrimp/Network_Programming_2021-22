#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool drukowalne_pointer(const char * buf)
{
    int i = 0;
    char *znak = (char *)buf + i;
    while(*znak != '\0')
    {
        if (*znak < 32 || *znak > 126)
        {
            return false;
        }
        i++;
        znak = (char *)buf + i;
    }

    return true;
}

bool drukowalne_array(const char * buf)
{
    int i = 0;
    while(buf[i] != '\0')
    {
        if (buf[i] < 32 || buf[i] > 126)
        {
            return false;
        }
        i++;
    }

    return true;
}

int main()
{
    char *bufor = "Ala ma kotaó";
    printf("%s\n", drukowalne_pointer(bufor)?"true":"false");
    printf("%s\n", drukowalne_array(bufor)?"true":"false");
}