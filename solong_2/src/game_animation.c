/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 16:55:25 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	update_coin_animation(t_game *g)
{
    const int   coin_delay = 12000;

    g->coin_tick++;
    if (g->coin_tick >= coin_delay)
    {
        g->coin_tick = 0;
        g->coin_frame = (g->coin_frame + 1) % 2;
    }
}

static void	update_idle_state(t_game *g)
{
    g->idle_tick++;
    if (g->idle_tick > 100000)
        g->idle_state = 1;
}

int	loop_animation(t_game *g)
{
    static int  frames = 0;

    frames++;
    if (frames % 1000 == 0)
        render(g);
    update_coin_animation(g);
    update_idle_state(g);
    return (0);
}

