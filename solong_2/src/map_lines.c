/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 16:31:39 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

static int	resize_array(char ***arr, int *cap)
{
	int		new_cap;
	char	**tmp;
	int		i;

	if (*cap == 0)
		new_cap = 8;
	else
		new_cap = *cap * 2;
	tmp = malloc(sizeof(char *) * new_cap);
	if (!tmp)
		return (0);
	i = 0;
	while (i < *cap)
	{
		tmp[i] = (*arr)[i];
		i++;
	}
	free(*arr);
	*arr = tmp;
	*cap = new_cap;
	return (1);
}

static int	push_line(char ***arr, int *cap, int *len, char *line)
{
	if (*len + 1 >= *cap)
	{
		if (!resize_array(arr, cap))
			return (0);
	}
	(*arr)[*len] = line;
	(*len)++;
	(*arr)[*len] = NULL;
	return (1);
}

int	read_map_lines(int fd, char ***lines, int *cap, int *len)
{
	char	*raw;

	raw = get_next_line(fd);
	while (raw)
	{
		raw = strip_newline(raw);
		if (!raw)
			return (0);
		if (!push_line(lines, cap, len, raw))
			return (0);
		raw = get_next_line(fd);
	}
	return (1);
}
