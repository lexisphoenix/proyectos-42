/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   game_render.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: anieto-m <anieto-m@student.42malaga.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/11 15:22:24 by anieto-m		  #+#	#+#			 */
/*   Updated: 2025/09/18 16:55:25 by anieto-m		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "game.h"
#include "ft_printf.h"
#include <stdlib.h>

static void	render_tile(t_game *g, int x, int y)
{
	char	tile_char;
	void	*tile;
	void	**player_array;
	int	 frame;

	tile_char = g->grid[y][x];
	tile = g->img_floor;
	if (tile_char == '1')
		tile = g->img_wall;
	else if (tile_char == 'C')
		tile = g->img_coin[g->coin_frame];
	else if (tile_char == 'E')
	{
		if (g->exit_flip && g->img_exit_flipped)
			tile = g->img_exit_flipped;
		else
			tile = g->img_exit;
	}
	else if (tile_char == 'P')
	{
		if (g->dir == 0)
			player_array = (void **)g->img_player_iz;
		else
			player_array = (void **)g->img_player_der;
		if (g->idle_state)
			frame = 3;
		else
			frame = g->player_frame;
		if (!player_array[frame])
			frame = 0;
		tile = player_array[frame];
	}
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

static void	render_ui(t_game *g)
{
	char	*moves_str;
	char	*info1;
	char	*coins_str;
	char	*info2;

	moves_str = ft_itoa(g->moves);
	if (!moves_str)
		return ;
	info1 = ft_strjoin("Moves: ", moves_str);
	if (info1)
		mlx_string_put(g->mlx, g->win, 10, 20, 0x00FF00, info1);
	coins_str = ft_itoa(g->remaining_c);
	info2 = ft_strjoin("Levels Left: ", coins_str);
	mlx_string_put(g->mlx, g->win, 10, 40, 0xFFFF00, info2);
	mlx_string_put(g->mlx, g->win, 100, 20, 0xFFFFFF, "My 42 journey");
	free(moves_str);
	free(coins_str);
	free(info2);
	if (info1)
		free(info1);
}

void	render(t_game *g)
{
	render_map(g);
	render_ui(g);
}
