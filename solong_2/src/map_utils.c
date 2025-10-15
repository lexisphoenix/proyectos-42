/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:55:05 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <unistd.h>

size_t	ft_strlen_custom(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	print_error(const char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen_custom(message));
	write(2, "\n", 1);
}

int	in_bounds(t_map *m, int x, int y)
{
	if (x >= 0 && x < m->w && y >= 0 && y < m->h)
		return (1);
	return (0);
}
