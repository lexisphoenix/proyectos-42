/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:50:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"
#include <stdlib.h>

static void	handle_movement_keys(int key, t_game *g)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (key == 119 || key == 65362)
		dy = -1;
	else if (key == 115 || key == 65364)
		dy = 1;
	else if (key == 97 || key == 65361)
		dx = -1;
	else if (key == 100 || key == 65363)
		dx = 1;
	if (dx || dy)
		try_move(g, dx, dy);
}

int	on_key_press(int key, t_game *g)
{
	if (key == 65307)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	handle_movement_keys(key, g);
	return (0);
}

int	on_window_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}

