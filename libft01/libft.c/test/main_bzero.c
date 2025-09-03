#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../libft.h"

int main(void)
{
    char buffer[10] = "abcdefghi";

    ft_bzero(buffer, 5);
    write(1, buffer, 10); // debería mostrar 5 nulls y luego "fghi"
    write(1, "\n", 1);

    // Con memset también podrías comparar:
    char buffer2[10] = "abcdefghi";
    memset(buffer2, 0, 5);
    write(1, buffer2, 10);
    write(1, "\n", 1);

    return 0;
}
