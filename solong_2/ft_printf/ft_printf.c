/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

static int	print_str(char *s)
{
	if (!s)
		return (write(1, "(null)", 6));
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

static int	print_nbr(long n)
{
	char	*str;
	int		len;

	str = ft_itoa(n);
	if (!str)
		return (0);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

static int	print_unsigned(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_uitoa(n); // si no tienes ft_uitoa, implementa una mini función local
	if (!str)
		return (0);
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (len);
}

/* Para hexadecimales y punteros implementa helpers similares */

static int	dispatch_format(char spec, va_list args)
{
	if (spec == 'c')
		return (print_char(va_arg(args, int)));
	else if (spec == 's')
		return (print_str(va_arg(args, char *)));
	else if (spec == 'd' || spec == 'i')
		return (print_nbr(va_arg(args, int)));
	else if (spec == 'u')
		return (print_unsigned(va_arg(args, unsigned int)));
	else if (spec == '%')
		return (print_char('%'));
	/* Falta print_hex y print_ptr si tu proyecto los requiere */
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;
	int		i;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
			count += dispatch_format(format[++i], args);
		else
			count += print_char(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
