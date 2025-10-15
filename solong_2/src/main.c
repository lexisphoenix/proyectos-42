/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:54:42 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include "../includes/game.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include <unistd.h>

extern size_t	ft_strlen_custom(const char *s);

static int	has_ber_extension(const char *s)
{
	size_t	n;

	n = ft_strlen_custom(s);
	if (n < 4)
		return (0);
	if (s[n - 4] == '.' && s[n - 3] == 'b'
		&& s[n - 2] == 'e' && s[n - 1] == 'r')
		return (1);
	return (0);
}

static int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Uso: ./so_long map.ber\n", 2);
		return (0);
	}
	if (!has_ber_extension(argv[1]))
	{
		ft_putstr_fd("Error: extensión debe ser .ber\n", 2);
		return (0);
	}
	return (1);
}

static int	load_and_start_game(char *map_path)
{
	t_map	m;

	m.grid = NULL;
	m.w = 0;
	m.h = 0;
	m.px = 0;
	m.py = 0;
	m.count_p = 0;
	m.count_c = 0;
	m.count_e = 0;
	if (!parse_map(map_path, &m))
	{
		ft_putstr_fd("Error al cargar el mapa\n", 2);
		return (0);
	}
	ft_printf("map %dx%d\n", m.w, m.h);
	if (!game_start(&m))
	{
		ft_putstr_fd("Error al iniciar MLX\n", 2);
		free_map(&m);
		return (0);
	}
	free_map(&m);
	return (1);
}

int	main(int argc, char **argv)
{
	if (!validate_arguments(argc, argv))
		return (1);
	if (!load_and_start_game(argv[1]))
		return (1);
	return (0);
}
