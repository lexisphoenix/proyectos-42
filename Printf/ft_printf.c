/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:50:36 by anieto-m          #+#    #+#             */
/*   Updated: 2025/05/29 14:51:09 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(va_list args, const char format)
{
	int	print_len = 0;

	if (format == 'c')
		print_len += ft_putchar(va_arg(args, int));
	else if (format == 's')
		print_len += ft_putstr(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		print_len += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		print_len += ft_putunsigned(va_arg(args, unsigned int));
	else if (format == 'x')
		print_len += ft_puthex(va_arg(args, unsigned int), 0);
	else if (format == 'X')
		print_len += ft_puthex(va_arg(args, unsigned int), 1);
	else if (format == 'p')
		print_len += ft_putptr(va_arg(args, unsigned long));
	else if (format == '%')
		print_len += ft_putchar('%');
	return (print_len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		print_len;

	i = 0;
	print_len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			print_len += ft_formats(args, format[++i]);
		else
			print_len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (print_len);
}

