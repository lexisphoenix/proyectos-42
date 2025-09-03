#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
    char src[] = "Hola mundo";
    char dst1[20];
    char dst2[20];
    size_t r1, r2;

    r1 = ft_strlcpy(dst1, src, 6);
    r2 = strlcpy(dst2, src, 6);

    printf("ft_strlcpy: %s (%zu)\n", dst1, r1);
    printf("strlcpy:    %s (%zu)\n", dst2, r2);

    return 0;
}
