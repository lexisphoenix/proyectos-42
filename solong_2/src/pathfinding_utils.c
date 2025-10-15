/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:48:37 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdlib.h>
#include <unistd.h>

extern void		print_error(const char *message);
extern int		in_bounds(t_map *m, int x, int y);

int	init_pathfinding_data(t_map *m, unsigned char **visited,
		t_queue **queue, int *total)
{
	*total = m->w * m->h;
	*visited = calloc(*total, 1);
	*queue = malloc(sizeof(t_queue) * *total);
	if (!*visited || !*queue)
	{
		free(*visited);
		free(*queue);
		print_error("Memoria (path)");
		return (0);
	}
	return (1);
}

void	process_cell(t_map *m, t_queue current, int *reached_coins,
		int *reached_exit)
{
	char	cell;

	cell = m->grid[current.y][current.x];
	if (cell == 'C')
		(*reached_coins)++;
	if (cell == 'E')
		*reached_exit = 1;
}

void	init_directions(int dirs[4][2])
{
	dirs[0][0] = 1;
	dirs[0][1] = 0;
	dirs[1][0] = -1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = 1;
	dirs[3][0] = 0;
	dirs[3][1] = -1;
}

static void	enqueue_neighbor(t_map *m, int nx, int ny, t_neighbors_ctx *ctx)
{
	int	idx;

	if (in_bounds(m, nx, ny) == 0)
		return ;
	if (m->grid[ny][nx] == '1')
		return ;
	idx = ny * m->w + nx;
	if (ctx->visited[idx])
		return ;
	ctx->visited[idx] = 1;
	ctx->queue[*ctx->tail].x = nx;
	ctx->queue[*ctx->tail].y = ny;
	(*ctx->tail)++;
}

void	explore_neighbors(t_map *m, t_queue current, t_neighbors_ctx *ctx)
{
	int	dirs[4][2];
	int	i;

	init_directions(dirs);
	i = 0;
	while (i < 4)
	{
		enqueue_neighbor(m, current.x + dirs[i][0],
			current.y + dirs[i][1], ctx);
		i++;
	}
}
