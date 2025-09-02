#include <stdio.h>
#include <string.h>
#include "../libft.h"

int main(void)
{
	char buffer1[20] = "Hola ";
	char buffer2[20] = "Hola ";

	size_t r1 = ft_strlcat(buffer1, "mundo", sizeof(buffer1));
	size_t r2 = strlcat(buffer2, "mundo", sizeof(buffer2));

	printf("ft_strlcat: %s (%zu)\n", buffer1, r1);
	printf("strlcat:    %s (%zu)\n", buffer2, r2);

	return 0;
}
