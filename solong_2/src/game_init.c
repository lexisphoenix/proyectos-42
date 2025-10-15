/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:54:32 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/game.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include <stdlib.h>

extern int		load_basic_textures(t_game *g);
extern void		load_coin_textures(t_game *g);
extern void		load_player_textures(t_game *g);
extern t_game	*allocate_game_memory(void);
extern void		init_map_data(t_game *g, t_map *m);
extern int		init_mlx(t_game *g);
extern int		create_window(t_game *g);
extern void		setup_hooks(t_game *g);

static int	init_game_graphics(t_game *g)
{
	if (!init_mlx(g))
		return (0);
	if (!load_basic_textures(g))
		return (0);
	load_coin_textures(g);
	load_player_textures(g);
	if (!create_window(g))
		return (0);
	return (1);
}

int	game_start(t_map *m)
{
	t_game	*g;

	g = allocate_game_memory();
	if (!g)
		return (0);
	init_map_data(g, m);
	if (!init_game_graphics(g))
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
