/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:07:39 by anieto-m          #+#    #+#             */
/*   Updated: 2025/07/20 21:24:55 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	LIBRARY
*	#include <ctype.h>
*	DESCRIPTION
*	The isascii() function tests for an ASCII character, which is any character 
*	between 0 and octal 0177 inclusive.
*	PARAMETERS
*	#1. The character to test.
*	RETURN VALUES
*	The isascii() function returns zero if the character tests false and returns 
*	non-zero if the character tests true.
*/

#include "libft.h"

int	ft_isascii(int c)
{
	if ((c < 0) || (c > 127))
		return (0);
	return (1);
}
