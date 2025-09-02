#include <stdio.h>
#include "../libft.h"

int main(void)
{
	const char *text = "42 Málaga mola mucho";

	printf("strchr: %s\n", ft_strchr(text, 'm'));   // primera 'm'
	printf("strrchr: %s\n", ft_strrchr(text, 'm')); // última 'm'

	printf("strchr (no existe): %s\n", ft_strchr(text, 'z'));  // NULL
	printf("strchr (null): %s\n", ft_strchr(text, '\0'));      // puntero a final

	return 0;
}
