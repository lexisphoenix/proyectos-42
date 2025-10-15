/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 19:08:16 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_game	*allocate_game_memory(void)
{
	t_game	*g;

	g = malloc(sizeof(t_game));
	if (!g)
		return (NULL);
	ft_bzero(g, sizeof(t_game));
	return (g);
}

void	init_map_data(t_game *g, t_map *m)
{
	g->ts = 64;
	g->w = m->w;
	g->h = m->h;
	g->grid = m->grid;
	g->px = m->px;
	g->py = m->py;
	g->remaining_c = m->count_c;
	g->dir = 1;
}

int	init_mlx(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		return (0);
	return (1);
}

int	create_window(t_game *g)
{
	g->win = mlx_new_window(g->mlx, g->w * g->ts, g->h * g->ts, "so_long");
	if (!g->win)
		return (0);
	return (1);
}

void	setup_hooks(t_game *g)
{
	mlx_key_hook(g->win, on_key_press, g);
	mlx_hook(g->win, 17, 0, on_window_close, g);
	mlx_loop_hook(g->mlx, loop_animation, g);
}
