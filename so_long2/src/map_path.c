/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:33:13 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:33:15 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>

typedef struct s_q
{
	int	x;
	int	y;
}	t_q;

static int	in_bounds(t_map *m, int x, int y)
{
	return (x >= 0 && x < m->w && y >= 0 && y < m->h);
}

int	check_path(t_map *m)
{
	int				total;
	unsigned char	*vis;
	t_q				*q;
	int				head;
	int				tail;

	total = m->w * m->h;
	vis = calloc(total, 1);
	q = malloc(sizeof(t_q) * total);
	if (!vis || !q)
		return (free(vis), free(q), err("Memoria (path)"), 0);
	head = 0;
	tail = 0;
	q[tail++] = (t_q){m->px, m->py};
	vis[m->py * m->w + m->px] = 1;
	while (head < tail)
		bfs_expand(m, q, vis, &head, &tail);
	free(q);
	free(vis);
	return (bfs_validate(m));
}
