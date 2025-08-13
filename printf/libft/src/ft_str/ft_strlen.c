/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:39:16 by anieto-m          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	LIBRARY
*	#include <string.h>
*	DESCRIPTION
*	The strlen() function computes the length of the string s.
*	PARAMETERS
*	#1. The string to compute length.
*	RETURN VALUES
*	The strlen() function returns the number of characters that precede the 
*	terminating NUL character.  
*/

#include "libft.h"
#include <stdlib.h>

size_t	ft_strlen(const char *s) // Compute the length of a string
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}
