/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:39:16 by anieto-m          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	LIBRARY
*	#include <ctype.h>
*	DESCRIPTION
*	The toupper() function converts a lower-case letter to the corresponding 
*	upper-case letter. The argument must be representable as an unsigned char 
*	or the value of EOF.
*	PARAMETERS
*	#1. The character to convert.
*	RETURN VALUES
*	If the argument is a lower-case letter, the toupper() function returns the 
*	corresponding upper-case letter if there is one; otherwise, the argument is 
*	returned unchanged.
*/

#include "libft.h"

int	ft_toupper(int c) // Convert a lowercase letter to uppercase
{
	if ((c >= 'a') && (c <= 'z'))
		c = c - 32;
	return (c);
}
