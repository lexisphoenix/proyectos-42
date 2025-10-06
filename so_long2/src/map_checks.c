/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:32:54 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:39:07 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

int	is_rectangular(t_map *m)
{
	int	y;

	if (m->h < 3 || m->w < 3)
		return (err("Mapa demasiado pequeño"), 0);
	y = 0;
	while (y < m->h)
	{
		if ((int)slen(m->grid[y]) != m->w)
			return (err("Mapa no rectangular"), 0);
		y++;
	}
	return (1);
}

int	closed_by_walls(t_map *m)
{
	int	x;
	int	y;

	x = 0;
	while (x < m->w)
	{
		if (m->grid[0][x] != '1' || m->grid[m->h - 1][x] != '1')
			return (err("Bordes sup/inf sin muro"), 0);
		x++;
	}
	y = 0;
	while (y < m->h)
	{
		if (m->grid[y][0] != '1' || m->grid[y][m->w - 1] != '1')
			return (err("Bordes laterales sin muro"), 0);
		y++;
	}
	return (1);
}

int	count_chars_in_map(t_map *m, int *cP, int *cC, int *cE)
{
	int	y;
	int	x;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (!check_char(m, x, y, cP, cC, cE))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	chars_and_counts(t_map *m)
{
	int	player_count;
	int	coin_count;
	int	exit_count;

	player_count = 0;
	coin_count = 0;
	exit_count = 0;
	if (!count_chars_in_map(m, &player_count, &coin_count, &exit_count))
		return (0);
	return (validate_counts(player_count, coin_count, exit_count, m));
}

