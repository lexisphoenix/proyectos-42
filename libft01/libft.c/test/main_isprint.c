#include <stdio.h>
#include "../libft.h"

int main(void)
{
    printf("ft_isprint('a') = %d\n", ft_isprint('a'));   // 1
    printf("ft_isprint(' ') = %d\n", ft_isprint(' '));   // 1
    printf("ft_isprint(31) = %d\n", ft_isprint(31));     // 0
    printf("ft_isprint(127) = %d\n", ft_isprint(127));   // 0
    printf("ft_isprint('\\n') = %d\n", ft_isprint('\n')); // 0
    return 0;
}
