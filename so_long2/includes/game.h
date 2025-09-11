/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 19:16:28 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "map.h"
# include "mlx.h"

typedef struct s_game {
	// MLX
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int   bpp;
	int   sl;
	int   endian;

	// mapa
	int   ts;		// tamaño tile px
	int   w, h;	  // ancho, alto en tiles
	char **grid;	 // mapa
	int   px, py;	// posición del jugador
	int   remaining_c;
	int   moves;

	// sprites estáticos
	void *img_wall;
	void *img_floor;

	// salida (animada tipo blackhole)
	void *img_exit;
	void *img_exit_flipped;
	int   exit_tick;
	int   exit_flip;

	// monedas
	void *img_coin[2];
	int   coin_frame;
	int   coin_tick;

	// jugador
	void *img_player_iz[4];
	void *img_player_der[4];
	int   player_frame; // 0-2 caminar
	int   dir;		  // 0=izq, 1=der
	int   idle_tick;
	int   idle_state;   // 0 activo, 1 idle

	// debug info
	int   tx, ty;	   // tamaño real cargado del xpm
} t_game;


int  game_start(t_map *m);
#endif
