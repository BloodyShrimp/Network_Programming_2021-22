#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool drukowalne_pointer(const void *buf, int len)
{
    char *znak;
    for (int i = 0; i < len; i++)
    {
        znak = (char *)buf + i;
        if (*znak < 32 || *znak > 126)
        {
            return false;
        }
    }

    return true;
}

bool drukowalne_array(const void *buf, int len)
{
    const char *znak = buf;
    for (int i = 0; i < len; i++)
    {
        if (znak[i] < 32 || znak[i] > 126)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    const char bufor[5] = {'\n',45,46,77,44};
    printf("%s\n", drukowalne_pointer(bufor, 5)?"true":"false");
    printf("%s\n", drukowalne_array(bufor, 5)?"true":"false");
}