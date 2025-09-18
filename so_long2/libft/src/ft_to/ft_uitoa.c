/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:38:28 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 12:47:08 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	char			*str;
	int				len;
	unsigned int	tmp;

	tmp = n;
	len = 1;
	while (tmp >= 10)
	{
		tmp /= 10;
		len++;
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}