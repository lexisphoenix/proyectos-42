/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:22:41 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:36:21 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "libft.h"
#include "ft_printf.h"

static void	render_tile(t_game *g, int x, int y)
{
	char	t;
	void	*tile;

	t = g->grid[y][x];
	tile = g->img_floor;
	if (t == '1')
		tile = g->img_wall;
	else if (t == 'C')
		tile = g->img_coin[g->coin_frame];
	else if (t == 'E')
		tile = get_exit_tile(g);
	else if (t == 'P')
		tile = get_player_tile(g);
	if (tile)
		mlx_put_image_to_window(g->mlx, g->win, tile, x * g->ts, y * g->ts);
}

static void	render_map(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->h)
	{
		x = 0;
		while (x < g->w)
		{
			render_tile(g, x, y);
			x++;
		}
		y++;
	}
}

void	render(t_game *g)
{
	char	*moves;
	char	*info1;
	char	*coins;
	char	*info2;

	render_map(g);
	moves = ft_itoa(g->moves);
	if (!moves)
		return ;
	info1 = ft_strjoin("Moves: ", moves);
	if (info1)
		mlx_string_put(g->mlx, g->win, 10, 20, 0x00FF00, info1);
	coins = ft_itoa(g->remaining_c);
	info2 = ft_strjoin("Levels Left: ", coins);
	mlx_string_put(g->mlx, g->win, 10, 40, 0xFFFF00, info2);
	mlx_string_put(g->mlx, g->win, 100, 20, 0xFFFFFF, "My 42 journey");
	free(moves);
	free(coins);
	free(info2);
	if (info1)
		free(info1);
}
