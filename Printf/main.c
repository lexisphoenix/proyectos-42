#include <stdio.h>
int main(void)
{
	int len1 = ft_printf("Mi número es: %d y en hex: %x\n", 42, 42);
	int len2 = printf("Mi número es: %d y en hex: %x\n", 42, 42);
	ft_printf("Longitud ft_printf: %d\n", len1);
	printf("Longitud printf: %d\n", len2);
}

