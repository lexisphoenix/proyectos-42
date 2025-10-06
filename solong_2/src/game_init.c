/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 16:55:25 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "ft_printf.h"
#include "libft.h"
#include <stdlib.h>

static t_game	*allocate_game_memory(void)
{
    t_game  *g;

    g = malloc(sizeof(t_game));
    if (!g)
        return (NULL);
    ft_bzero(g, sizeof(t_game));
    return (g);
}

static void	init_map_data(t_game *g, t_map *m)
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

static int	init_mlx(t_game *g)
{
    g->mlx = mlx_init();
    if (!g->mlx)
        return (0);
    return (1);
}

static int	load_basic_textures(t_game *g)
{
    g->img_floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", 
                                         &g->tx, &g->ty);
    g->img_wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", 
                                        &g->tx, &g->ty);
    g->img_exit = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm", 
                                        &g->tx, &g->ty);
    g->img_exit_flipped = mlx_xpm_file_to_image(g->mlx, 
                                                "assets/exit_flipped.xpm", 
                                                &g->tx, &g->ty);
    if (!g->img_floor || !g->img_wall || !g->img_exit)
    {
        ft_printf("Error: no se pudieron cargar texturas críticas\n");
        return (0);
    }
    return (1);
}

static void	load_coin_textures(t_game *g)
{
    g->img_coin[0] = mlx_xpm_file_to_image(g->mlx, "assets/up/up1.xpm", 
                                           &g->tx, &g->ty);
    g->img_coin[1] = mlx_xpm_file_to_image(g->mlx, "assets/up/up2.xpm", 
                                           &g->tx, &g->ty);
    if (!g->img_coin[0] && g->img_coin[1])
        g->img_coin[0] = g->img_coin[1];
}

static void	load_player_textures(t_game *g)
{
    g->img_player_iz[0] = mlx_xpm_file_to_image(g->mlx, 
                                                "assets/player/mono1iz.xpm", 
                                                &g->tx, &g->ty);
    g->img_player_iz[1] = mlx_xpm_file_to_image(g->mlx, 
                                                "assets/player/mono2iz.xpm", 
                                                &g->tx, &g->ty);
    g->img_player_iz[2] = mlx_xpm_file_to_image(g->mlx, 
                                                "assets/player/mono3iz.xpm", 
                                                &g->tx, &g->ty);
    g->img_player_iz[3] = mlx_xpm_file_to_image(g->mlx, 
                                                "assets/player/mono4iz.xpm", 
                                                &g->tx, &g->ty);
    g->img_player_der[0] = mlx_xpm_file_to_image(g->mlx, 
                                                 "assets/player/mono1der.xpm", 
                                                 &g->tx, &g->ty);
    g->img_player_der[1] = mlx_xpm_file_to_image(g->mlx, 
                                                 "assets/player/mono2der.xpm", 
                                                 &g->tx, &g->ty);
    g->img_player_der[2] = mlx_xpm_file_to_image(g->mlx, 
                                                 "assets/player/mono3der.xpm", 
                                                 &g->tx, &g->ty);
    g->img_player_der[3] = mlx_xpm_file_to_image(g->mlx, 
                                                 "assets/player/mono4der.xpm", 
                                                 &g->tx, &g->ty);
}

static int	create_window(t_game *g)
{
    g->win = mlx_new_window(g->mlx, g->w * g->ts, g->h * g->ts, "so_long");
    if (!g->win)
        return (0);
    return (1);
}

static void	setup_hooks(t_game *g)
{
    mlx_key_hook(g->win, (int (*)(int, void *))on_key_press, g);
    mlx_hook(g->win, 17, 0, (int (*)(void *))on_window_close, g);
    mlx_loop_hook(g->mlx, (int (*)(void *))loop_animation, g);
}

int	game_start(t_map *m)
{
    t_game  *g;

    g = allocate_game_memory();
    if (!g)
        return (0);
    init_map_data(g, m);
    if (!init_mlx(g))
    {
        free(g);
        return (0);
    }
    if (!load_basic_textures(g))
    {
        free(g);
        return (0);
    }
    load_coin_textures(g);
    load_player_textures(g);
    if (!create_window(g))
    {
        free(g);
        return (0);
    }
    render(g);
    setup_hooks(g);
    mlx_loop(g->mlx);
    free(g);
    return (1);
}

