/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:23:38 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:29:29 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	init_game_data(t_game *g, t_map *m)
{
	ft_bzero(g, sizeof(t_game));
	g->ts = 64;
	g->w = m->w;
	g->h = m->h;
	g->grid = m->grid;
	g->px = m->px;
	g->py = m->py;
	g->remaining_c = m->count_c;
	g->dir = 1;
}

static int	init_window_and_assets(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	if (!load_assets(g))
	{
		ft_printf("Error: texturas críticas\n");
		return (0);
	}
	g->win = mlx_new_window(g->mlx, g->w * g->ts, g->h * g->ts, "so_long");
	return (1);
}

static void	set_hooks(t_game *g)
{
	mlx_key_hook(g->win, (int (*)(int, void *))on_key, g);
	mlx_hook(g->win, 17, 0, (int (*)(void *))on_close, g);
	mlx_loop_hook(g->mlx, (int (*)(void *))loop_anim, g);
}

int	game_start(t_map *m)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return (0);
	init_game_data(g, m);
	if (!init_window_and_assets(g))
		return (free(g), 0);
	render(g);
	set_hooks(g);
	mlx_loop(g->mlx);
	free(g);
	return (1);
}
