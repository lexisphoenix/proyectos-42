/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:44:11 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "game.h"
#include "ft_printf.h"
#include "utils.h"

int	validate_args(int argc, char **argv)
{
	if (argc != 2)
	{
		putstr(2, "Uso: ./check map.ber\n");
		return (0);
	}
	if (!has_ber_ext(argv[1]))
	{
		putstr(2, "Error: extensión debe ser .ber\n");
		return (0);
	}
	return (1);
}

int	run_game(const char *path)
{
	int		y;
	t_map	m;

	m = (t_map){0};
	if (!parse_map(path, &m))
	{
		putstr(2, "Error al cargar el mapa\n");
		return (0);
	}
	ft_printf("map %dx%d\n", m.w, m.h);
	if (!game_start(&m))
	{
		putstr(2, "Error al iniciar MLX\n");
		free_map(&m);
		return (0);
	}
	y = 0;
	while (y < m.h)
	{
		putstr(1, m.grid[y]);
		putstr(1, "\n");
		y++;
	}
	free_map(&m);
	return (1);
}

int	main(int argc, char **argv)
{
	if (!validate_args(argc, argv))
		return (1);
	if (!run_game(argv[1]))
		return (1);
	return (0);
}
