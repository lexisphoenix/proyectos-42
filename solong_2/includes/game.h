/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 19:52:59 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "map.h"
# include "../minilibx/linux/mlx.h"

typedef struct s_game
{
	void	*mlx; // mlx instance
	void	*win; 	// window
	void	*img; // current image
	char	*addr; // image address
	int		bpp; // bits per pixel
	int		sl; // size line
	int		endian; // endianess
	int		ts; // tile size
	int		w; // map width
	int		h;	// map height
	char	**grid; 	// map grid
	int		px; 	
	int		py;	 // player position
	int		remaining_c; 	// remaining coins
	int		moves; 	// move count
	void	*img_wall; // wall image
	void	*img_floor; // floor image
	void	*img_exit; 	// exit image
	void	*img_exit_flipped; // exit image when flipped
	int		exit_tick; // exit animation tick
	int		exit_flip; // exit flip state
	void	*img_coin[2]; // coin images for animation
	int		coin_frame; // current coin frame
	int		coin_tick; 	// coin animation tick
	void	*img_player_iz[4]; // player left images 
	void	*img_player_der[4];	 // player right images 
	int		player_frame;	 // current player frame 
	int		dir; // player direction (0 left, 1 right)
	int		idle_tick; // idle animation tick
	int		idle_state; // idle animation state
	int		tx;	// target x for movement animation
	int		ty; // target y for movement animation
}		t_game;

int		game_start(t_map	*m);
void	render(t_game	*g);
int		loop_animation(t_game	*g);
int		try_move(t_game *g, int dx, int dy);
int		on_key_press(int key,	t_game	*g);
int		on_window_close(t_game	*g);

#endif
