/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:57:57 by anieto-m          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putptr(unsigned long ptr)
{
	int	len = 0;

	len += ft_putstr("0x");
	if (ptr == 0)
		return (len + ft_putchar('0'));
	if (ptr >= 16)
		len += ft_putptr(ptr / 16);
	len += ft_putchar("0123456789abcdef"[ptr % 16]);
	return (len);
}

