/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 15:11:15 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	jump_line(char *str) //
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join_and_free(char *str1, char *str2)
{
	char	*rest;
	int		i;
	int		j;

	if (!str1 && !str2)
		return (NULL);
	rest = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!rest)
	{
		free(str1);
		return (NULL);
	}
	i = 0;
	while (str1 && str1[i])
	{
		rest[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2 && str2[j])
		rest[i++] = str2[j++];
	rest[i] = '\0';
	free(str1);
	return (rest);
}