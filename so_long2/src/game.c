/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 20:24:42 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"   // para ft_printf
#include <stdlib.h>      // para exit()
#include "game.h"
#include <unistd.h>

// ---------------------- RENDER ----------------------

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
		tile = (g->exit_flip ? g->img_exit_flipped : g->img_exit);
	else if (t == 'P')
	{
		if (g->idle_state)
			tile = (g->dir == 0 ? g->img_player_iz[3] : g->img_player_der[3]);
		else
			tile = (g->dir == 0 ? g->img_player_iz[g->player_frame]
					: g->img_player_der[g->player_frame]);
	}
	if (tile)
		mlx_put_image_to_window(g->mlx, g->win, tile, x * g->ts, y * g->ts);
}

static void	render(t_game *g)
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
	// --- dibujar contador ---
	ft_printf("Moves: %d\n", g->moves);
}

// ---------------------- LOOP ANIM ----------------------

static int	loop_anim(t_game *g)
{
	// animación de la moneda
	const int	coin_delay = 60;

	g->coin_tick++;
	if (g->coin_tick >= coin_delay)
	{
		g->coin_tick = 0;
		g->coin_frame = (g->coin_frame + 1) % 2;
	}
	// reposo del mono
	g->idle_tick++;
	if (g->idle_tick > 300)
		g->idle_state = 1;
	render(g);
	return (0);
}

// ---------------------- MOVIMIENTO ----------------------

static int	try_move(t_game *g, int dx, int dy)
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
		{
			ft_printf("You win!\n");
			mlx_destroy_window(g->mlx, g->win);
			exit(0);
		}
		return (0);
	}
	g->grid[g->py][g->px] = '0';
	g->grid[ny][nx] = 'P';
	g->px = nx;
	g->py = ny;
	g->moves++;
	if (dx < 0)
		g->dir = 0;
	if (dx > 0)
		g->dir = 1;
	g->player_frame = (g->player_frame + 1) % 3;
	ft_printf("Moves: %d, C left: %d\n", g->moves, g->remaining_c);
	g->idle_tick = 0;
	g->idle_state = 0;
	render(g);
	return (1);
}

// ---------------------- HOOKS ----------------------

static int	on_key(int key, t_game *g)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	if (key == 13 || key == 126)
		dy = -1;
	else if (key == 1 || key == 125)
		dy = 1;
	else if (key == 0 || key == 123)
		dx = -1;
	else if (key == 2 || key == 124)
		dx = 1;
	if (dx || dy)
		try_move(g, dx, dy);
	return (0);
}

static int	on_close(t_game *g)
{
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return (0);
}

// ---------------------- START ----------------------

int	game_start(t_map *m)
{
	t_game	g;

	g.ts = 64;
	g.w = m->w;
	g.h = m->h;
	g.grid = m->grid;
	g.px = m->px;
	g.py = m->py;
	g.remaining_c = m->count_c;
	g.moves = 0;
	g.mlx = mlx_init();
	if (!g.mlx)
		return (0);
	// Carga mínima (ajusta a tus assets)
	g.img_floor = mlx_xpm_file_to_image(g.mlx, "assets/floor.xpm", &g.tx, &g.ty);
	g.img_wall = mlx_xpm_file_to_image(g.mlx, "assets/wall.xpm", &g.tx, &g.ty);
	g.img_exit = mlx_xpm_file_to_image(g.mlx, "assets/exit.xpm", &g.tx, &g.ty);
	g.img_coin[0] = mlx_xpm_file_to_image(g.mlx, "assets/up/up1.xpm", &g.tx, &g.ty);
	g.img_coin[1] = mlx_xpm_file_to_image(g.mlx, "assets/up/up2.xpm", &g.tx, &g.ty);
	g.img_player_iz[0] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono1iz.xpm", &g.tx, &g.ty);
	g.img_player_der[0] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono1der.xpm", &g.tx, &g.ty);
	g.player_frame = 0;
	g.coin_frame = 0;
	g.coin_tick = 0;
	g.idle_tick = 0;
	g.idle_state = 0;
	g.win = mlx_new_window(g.mlx, g.w * g.ts, g.h * g.ts, "so_long");
	render(&g);
	mlx_key_hook(g.win, (int (*)(int, void *))on_key, &g);
	mlx_hook(g.win, 17, 0, (int (*)(void *))on_close, &g);
	mlx_loop_hook(g.mlx, (int (*)(void *))loop_anim, &g);
	mlx_loop(g.mlx);
	return (1);
}
