/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 15:15:47 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "game.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

// --- RENDER ---
static void	render_tile(t_game *g, int x, int y)
{
	char	t = g->grid[y][x];
	void	*tile = g->img_floor;

	if (t == '1')
		tile = g->img_wall;
	else if (t == 'C')
		tile = g->img_coin[g->coin_frame];
	else if (t == 'E')
		tile = (g->exit_flip && g->img_exit_flipped)
			? g->img_exit_flipped
			: g->img_exit;
	else if (t == 'P')
	{
		// fallback automático: usa frame 0 si no hay frame N cargado
		void **arr = (g->dir == 0)
			? (void **)g->img_player_iz
			: (void **)g->img_player_der;
		int frame = (g->idle_state ? 3 : g->player_frame);
		if (!arr[frame])
			frame = 0;
		tile = arr[frame];
	}
	if (tile)
		mlx_put_image_to_window(g->mlx, g->win, tile, x * g->ts, y * g->ts);
}

static void	render(t_game *g)
{
	char *moves_str;
	char *msg;

	for (int y = 0; y < g->h; y++)
		for (int x = 0; x < g->w; x++)
			render_tile(g, x, y);

	moves_str = ft_itoa(g->moves);
	if (!moves_str)
		return ;

	msg = ft_strjoin("Moves: ", moves_str);
	if (msg)
		mlx_string_put(g->mlx, g->win, 10, 20, 0xFFFFFF, msg);

	free(moves_str);
	if (msg)
		free(msg);
}

// --- LOOP ANIM ---
static int	loop_anim(t_game *g)
{
	const int	coin_delay = 300;

	if (++g->coin_tick >= coin_delay)
	{
		g->coin_tick = 0;
		g->coin_frame = (g->coin_frame + 1) % 2;
	}
	if (++g->idle_tick > 300)
		g->idle_state = 1;
	render(g);
	return (0);
}

// --- MOVIMIENTO ---
static int	try_move(t_game *g, int dx, int dy)
{
	int nx = g->px + dx, ny = g->py + dy;
	if (nx < 0 || nx >= g->w || ny < 0 || ny >= g->h) return 0;
	char dest = g->grid[ny][nx];
	if (dest == '1') return 0;
	if (dest == 'C') g->remaining_c--;
	if (dest == 'E' && g->remaining_c == 0)
	{
		ft_printf("You win!\n");
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	g->grid[g->py][g->px] = '0';
	g->grid[ny][nx] = 'P';
	g->px = nx; g->py = ny;
	g->moves++;
	g->dir = (dx < 0) ? 0 : (dx > 0) ? 1 : g->dir;
	g->player_frame = (g->player_frame + 1) % 3;
	g->idle_tick = 0;
	g->idle_state = 0;
	render(g);
	return 1;
}

// --- HOOKS ---
static int	on_key(int key, t_game *g)
{
	int dx=0, dy=0;
	if (key == 65307) // ESC
	{ mlx_destroy_window(g->mlx, g->win); exit(0); }
	if (key == 119 || key == 65362) dy = -1;
	else if (key == 115 || key == 65364) dy = 1;
	else if (key == 97 || key == 65361) dx = -1;
	else if (key == 100 || key == 65363) dx = 1;
	if (dx || dy) try_move(g, dx, dy);
	return 0;
}

static int	on_close(t_game *g)
{ mlx_destroy_window(g->mlx, g->win); exit(0); return 0; }

// --- START ---
int	game_start(t_map *m)
{
	t_game	*g;

	// Reservar memoria para el estado del juego
	g = malloc(sizeof(t_game));
	if (!g)
		return (0);
	ft_bzero(g, sizeof(t_game));

	// Inicializar datos del mapa
	g->ts = 64;
	g->w = m->w;
	g->h = m->h;
	g->grid = m->grid;
	g->px = m->px;
	g->py = m->py;
	g->remaining_c = m->count_c;
	g->dir = 1; // empieza mirando a la derecha

	// Inicializar MLX
	g->mlx = mlx_init();
	if (!g->mlx)
		return (free(g), 0);

	// --- Cargar imágenes ---
	g->img_floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", &g->tx, &g->ty);
	g->img_wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", &g->tx, &g->ty);
	g->img_exit = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm", &g->tx, &g->ty);
	g->img_exit_flipped = mlx_xpm_file_to_image(g->mlx, "assets/exit_flipped.xpm", &g->tx, &g->ty);

	g->img_coin[0] = mlx_xpm_file_to_image(g->mlx, "assets/up/up1.xpm", &g->tx, &g->ty);
	g->img_coin[1] = mlx_xpm_file_to_image(g->mlx, "assets/up/up2.xpm", &g->tx, &g->ty);
	if (!g->img_coin[0] && g->img_coin[1])
		g->img_coin[0] = g->img_coin[1];

	// Jugador (cargar todos los frames que existan)
	g->img_player_iz[0] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono1iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[1] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono2iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[2] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono3iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[3] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono4iz.xpm", &g->tx, &g->ty);

	g->img_player_der[0] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono1der.xpm", &g->tx, &g->ty);
	g->img_player_der[1] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono2der.xpm", &g->tx, &g->ty);
	g->img_player_der[2] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono3der.xpm", &g->tx, &g->ty);
	g->img_player_der[3] = mlx_xpm_file_to_image(g->mlx, "assets/player/mono4der.xpm", &g->tx, &g->ty);

	// Validación mínima de assets críticos
	if (!g->img_floor || !g->img_wall || !g->img_exit)
	{
		ft_printf("Error: no se pudieron cargar texturas críticas\n");
		return (free(g), 0);
	}

	// Crear ventana
	g->win = mlx_new_window(g->mlx, g->w * g->ts, g->h * g->ts, "so_long");

	// Primer render
	render(g);

	// Hooks
	mlx_key_hook(g->win, (int (*)(int, void *))on_key, g);
	mlx_hook(g->win, 17, 0, (int (*)(void *))on_close, g);
	mlx_loop_hook(g->mlx, (int (*)(void *))loop_anim, g);

	// Bucle principal
	mlx_loop(g->mlx);

	// Si alguna vez sales del loop, libera memoria
	free(g);
	return (1);
}
