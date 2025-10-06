/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:33:45 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:33:49 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	bfs_expand(t_map *m, t_q *q, unsigned char *vis, int *head, int *tail)
{
	int	dirs[4][2];
	int	i;
	t_q	cur;

	dirs[0][0] = 1;
	dirs[0][1] = 0;
	dirs[1][0] = -1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = 1;
	dirs[3][0] = 0;
	dirs[3][1] = -1;
	cur = q[*head];
	(*head)++;
	update_cell(m, cur.x, cur.y);
	i = 0;
	while (i < 4)
	{
		bfs_try_push(m, q, vis, tail, cur.x + dirs[i][0], cur.y + dirs[i][1]);
		i++;
	}
}
