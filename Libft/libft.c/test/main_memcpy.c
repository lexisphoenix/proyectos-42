#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    char src[] = "Hola mundo";
    char dst1[20];
    char dst2[20];

    ft_memcpy(dst1, src, 11);
    memcpy(dst2, src, 11);

    printf("ft_memcpy: %s\n", dst1);
    printf("memcpy:    %s\n", dst2);

    return 0;
}
