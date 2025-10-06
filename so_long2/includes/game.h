/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 15:05:56 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "map.h"
# include "mlx.h"

typedef struct s_game
{
	/* MLX */
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;

	/* Mapa */
	int		ts;/* tamaño tile px */
	int		w;/* ancho en tiles */
	int		h;/* alto en tiles */
	char	**grid;
	int		px;
	int		py;/* posición del jugador */
	int		remaining_c;
	int		moves;

	/* Sprites estáticos */
	void	*img_wall;
	void	*img_floor;

	/* Salida (puerta animada) */
	void	*img_exit;
	void	*img_exit_flipped;
	int		exit_tick;
	int		exit_flip;

	/* Monedas */
	void	*img_coin[2];
	int		coin_frame;
	int		coin_tick;

	/* Jugador */
	void	*img_player_iz[4];
	void	*img_player_der[4];
	int		player_frame;
	int		dir;/* 0 = izq, 1 = der */
	int		idle_tick;
	int		idle_state; /* 0 activo, 1 idle */

	/* Debug info */
	int		tx; /* tamaño real del xpm */
	int		ty;
}	t_game;

/* Funciones públicas */
int		game_start(t_map *m);
void	*get_exit_tile(t_game *g);
void	*get_player_tile(t_game *g);
void	render(t_game *g);

/* --- FUNCIONES AUXILIARES (usadas en game_start.c) --- */
int		load_assets(t_game *g);
int		on_key(int key, t_game *g);
int		on_close(t_game *g);
int		loop_anim(t_game *g);

#endif
