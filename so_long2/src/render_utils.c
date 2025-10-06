/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:35:57 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:36:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	*get_exit_tile(t_game *g)
{
	if (g->exit_flip && g->img_exit_flipped)
		return (g->img_exit_flipped);
	return (g->img_exit);
}

void	*get_player_tile(t_game *g)
{
	void	**arr;
	int		frame;

	if (g->dir == 0)
		arr = (void **)g->img_player_iz;
	else
		arr = (void **)g->img_player_der;
	if (g->idle_state)
		frame = 3;
	else
		frame = g->player_frame;
	if (!arr[frame])
		frame = 0;
	return (arr[frame]);
}
