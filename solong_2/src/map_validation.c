/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:55:09 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <unistd.h>

extern size_t	ft_strlen_custom(const char *s);
extern void		print_error(const char *message);

int	is_rectangular(t_map *m)
{
	int	y;

	if (m->h < 3 || m->w < 3)
	{
		print_error("Mapa demasiado pequeño");
		return (0);
	}
	y = 0;
	while (y < m->h)
	{
		if ((int)ft_strlen_custom(m->grid[y]) != m->w)
		{
			print_error("Mapa no rectangular");
			return (0);
		}
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
		{
			print_error("Bordes sup/inf sin muro");
			return (0);
		}
		x++;
	}
	y = 0;
	while (y < m->h)
	{
		if (m->grid[y][0] != '1' || m->grid[y][m->w - 1] != '1')
		{
			print_error("Bordes laterales sin muro");
			return (0);
		}
		y++;
	}
	return (1);
}

static int	validate_char(char c, t_validation_data *data, int x, int y)
{
	if (c != '0' && c != '1' && c != 'C' && c != 'E' && c != 'P')
	{
		print_error("Carácter inválido");
		return (0);
	}
	if (c == 'P')
	{
		data->count_p++;
		data->m->px = x;
		data->m->py = y;
	}
	else if (c == 'C')
		data->count_c++;
	else if (c == 'E')
		data->count_e++;
	return (1);
}

static int	validate_counts(int count_p, int count_c, int count_e, t_map *m)
{
	if (count_p != 1)
	{
		print_error("Debe haber exactamente 1 P");
		return (0);
	}
	if (count_c < 1)
	{
		print_error("Debe haber al menos 1 C");
		return (0);
	}
	if (count_e < 1)
	{
		print_error("Debe haber al menos 1 E");
		return (0);
	}
	m->count_p = count_p;
	m->count_c = count_c;
	m->count_e = count_e;
	return (1);
}

int	validate_characters_and_counts(t_map *m)
{
	t_validation_data	data;
	int					y;
	int					x;

	data.count_p = 0;
	data.count_c = 0;
	data.count_e = 0;
	data.m = m;
	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (!validate_char(m->grid[y][x], &data, x, y))
				return (0);
			x++;
		}
		y++;
	}
	return (validate_counts(data.count_p, data.count_c, data.count_e, m));
}
