/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:53:43 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:52:36 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H
# include "map.h"
# include "mlx.h"

typedef struct s_game
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bpp;
    int     sl;
    int     endian;
    int     ts;
    int     w;
    int     h;
    char    **grid;
    int     px;
    int     py;
    int     remaining_c;
    int     moves;
    void    *img_wall;
    void    *img_floor;
    void    *img_exit;
    void    *img_exit_flipped;
    int     exit_tick;
    int     exit_flip;
    void    *img_coin[2];
    int     coin_frame;
    int     coin_tick;
    void    *img_player_iz[4];
    void    *img_player_der[4];
    int     player_frame;
    int     dir;
    int     idle_tick;
    int     idle_state;
    int     tx;
    int     ty;
}   t_game;

int     game_start(t_map *m);
void    render(t_game *g);
int     loop_animation(t_game *g);
int     try_move(t_game *g, int dx, int dy);
int     on_key_press(int key, t_game *g);
int     on_window_close(t_game *g);

#endif
