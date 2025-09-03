#include <stdio.h>
#include "../libft.h"

int main(void)
{
    printf("ft_isascii(65) = %d\n", ft_isascii(65));   // 1
    printf("ft_isascii(128) = %d\n", ft_isascii(128)); // 0
    printf("ft_isascii(0) = %d\n", ft_isascii(0));     // 1
    printf("ft_isascii(-1) = %d\n", ft_isascii(-1));   // 0
    return 0;
}
