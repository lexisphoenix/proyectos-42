/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:02:04 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 19:16:16 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex(unsigned int num, int upper)
{
	char	*base;
	int		len = 0;

	base = (upper ? "0123456789ABCDEF" : "0123456789abcdef");
	if (num >= 16)
		len += ft_puthex(num / 16, upper);
	len += ft_putchar(base[num % 16]);
	return (len);
}

