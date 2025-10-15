/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:20:00 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:31:39 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdlib.h>

int	is_whitespace(char c)
{
	return (c == '\n' || c == '\r' || c == ' ' || c == '\t');
}

char	*strip_newline(char *s)
{
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen_custom(s);
	while (n && is_whitespace(s[n - 1]))
	{
		n--;
		s[n] = '\0';
	}
	if (n == 0)
	{
		free(s);
		return (NULL);
	}
	return (s);
}
