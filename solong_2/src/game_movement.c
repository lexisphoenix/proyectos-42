/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 17:08:25 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"
#include "../ft_printf/ft_printf.h"
#include <stdlib.h>

static int	is_valid_position(t_game *g, int nx, int ny)
{
	if (nx < 0 || nx >= g->w || ny < 0 || ny >= g->h)
		return (0);
	return (1);
}

static int	handle_exit(t_game *g, int nx, int ny)
{
	(void)nx;
	(void)ny;
	if (g->remaining_c == 0)
	{
		ft_printf("You win! All coins collected!\n");
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	ft_printf("You need to collect all coins first! (%d remaining)\n",
		g->remaining_c);
	return (0);
}

static void	update_player_position(t_game *g, int nx, int ny, int dx)
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
}

int	try_move(t_game *g, int dx, int dy)
{
	int		nx;
	int		ny;
	char	dest;

	nx = g->px + dx;
	ny = g->py + dy;
	if (!is_valid_position(g, nx, ny))
		return (0);
	dest = g->grid[ny][nx];
	if (dest == '1')
		return (0);
	if (dest == 'C')
		g->remaining_c--;
	if (dest == 'E')
		return (handle_exit(g, nx, ny));
	update_player_position(g, nx, ny, dx);
	render(g);
	return (1);
}
