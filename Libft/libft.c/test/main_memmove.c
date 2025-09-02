#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    char buffer1[20] = "1234567890";
    char buffer2[20] = "1234567890";

    ft_memmove(buffer1 + 2, buffer1, 5);
    memmove(buffer2 + 2, buffer2, 5);

    printf("ft_memmove: %s\n", buffer1);  // Resultado correcto
    printf("memmove:    %s\n", buffer2);  // Igual al anterior

    return 0;
}
