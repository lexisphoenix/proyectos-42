/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loader.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:55:18 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"

int	load_basic_textures(t_game *g)
{
	g->img_floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm",
			&g->tx, &g->ty);
	g->img_wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm",
			&g->tx, &g->ty);
	g->img_exit = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm",
			&g->tx, &g->ty);
	g->img_exit_flipped = mlx_xpm_file_to_image(g->mlx,
			"assets/exit_flipped.xpm", &g->tx, &g->ty);
	if (!g->img_floor || !g->img_wall || !g->img_exit)
	{
		return (0);
	}
	return (1);
}

void	load_coin_textures(t_game *g)
{
	g->img_coin[0] = mlx_xpm_file_to_image(g->mlx, "assets/up/up1.xpm",
			&g->tx, &g->ty);
	g->img_coin[1] = mlx_xpm_file_to_image(g->mlx, "assets/up/up2.xpm",
			&g->tx, &g->ty);
	if (!g->img_coin[0] && g->img_coin[1])
		g->img_coin[0] = g->img_coin[1];
}

void	load_player_textures(t_game *g)
{
	g->img_player_iz[0] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono1iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[1] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono2iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[2] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono3iz.xpm", &g->tx, &g->ty);
	g->img_player_iz[3] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono4iz.xpm", &g->tx, &g->ty);
	g->img_player_der[0] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono1der.xpm", &g->tx, &g->ty);
	g->img_player_der[1] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono2der.xpm", &g->tx, &g->ty);
	g->img_player_der[2] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono3der.xpm", &g->tx, &g->ty);
	g->img_player_der[3] = mlx_xpm_file_to_image(g->mlx,
			"assets/player/mono4der.xpm", &g->tx, &g->ty);
}
