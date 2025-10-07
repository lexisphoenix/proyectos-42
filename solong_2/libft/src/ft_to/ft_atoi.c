/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	LIBRARY
*	#include <stdlib.h>
*	DESCRIPTION
*	The atoi() function converts the initial portion of the string pointed to by 
*	str to int representation.
*	PARAMETERS
*	#1. The string to convert to integer.
*	RETURN VALUES
*	The atoi() function returns its converted int representation.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	cnt;
	int	neg;
	int	num;

	cnt = 0;
	neg = 1;
	num = 0;
	if (!str)
		return (0);
	while ((str[cnt] >= '\t' && str[cnt] <= '\r') || str[cnt] == ' ')
		cnt++;
	if (str[cnt] == '-')
		neg = -1;
	if (str[cnt] == '+' || str[cnt] == '-')
		cnt++;
	while (str[cnt] >= '0' && str[cnt] <= '9')
	{
		num = (str[cnt] - '0') + (num * 10);
		cnt++;
	}
	return (num * neg);
}
