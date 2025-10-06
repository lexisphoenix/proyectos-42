/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:23:00 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:25:00 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	handle_exit_tile(t_game *g)
{
	ft_printf("You win!\n");
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
}

static void	update_player_pos(t_game *g, int nx, int ny, int dx)
{
	g->grid[g->py][g->px] = '0';
	g->grid[ny][nx] = 'P';
	g->px = nx;
	g->py = ny;
	g->moves++;
	if (dx < 0)
		g->dir = 0;
	else if (dx > 0)
		g->dir = 1;
	g->player_frame = (g->player_frame + 1) % 3;
	g->idle_tick = 0;
	g->idle_state = 0;
	render(g);
}

int	try_move(t_game *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	dest;

	nx = g->px + dx;
	ny = g->py + dy;
	if (nx < 0 || nx >= g->w || ny < 0 || ny >= g->h)
		return (0);
	dest = g->grid[ny][nx];
	if (dest == '1')
		return (0);
	if (dest == 'C')
		g->remaining_c--;
	if (dest == 'E')
	{
		if (g->remaining_c == 0)
			handle_exit_tile(g);
		return (0);
	}
	update_player_pos(g, nx, ny, dx);
	return (1);
}

int	on_key(int key, t_game *g)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (key == 65307)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
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
	return (0);
}

int	on_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}
