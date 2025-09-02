#include <stdio.h>
#include "../libft.h"

int main(void)
{
	printf("toupper('a') = %c\n", ft_toupper('a')); // A
	printf("toupper('A') = %c\n", ft_toupper('A')); // A
	printf("tolower('Z') = %c\n", ft_tolower('Z')); // z
	printf("tolower('z') = %c\n", ft_tolower('z')); // z
	printf("tolower('!') = %c\n", ft_tolower('!')); // !
	return 0;
}
