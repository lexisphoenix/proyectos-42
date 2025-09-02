#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    char buffer[10] = "string";

    ft_memset(buffer, 'x', 5);
    printf("ft_memset: %s\n", buffer);
    return 0;
}
