/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 19:18:02 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdlib.h>
#include <unistd.h>

extern int		in_bounds(t_map *m, int x, int y);
extern void		print_error(const char *message);
extern int		init_pathfinding_data(t_map *m, unsigned char	**visited,
					t_queue **queue,
					int *total);
extern void		process_cell(t_map *m,
					t_queue current,
					int *reached_coins,
					int *reached_exit);
extern void		explore_neighbors(t_map *m,
					t_queue current,
					t_neighbors_ctx *ctx);

static void	process_head(t_map *m, t_pathfinding_data *data,
					t_neighbors_ctx *ctx, int head)
{
	process_cell(m, data->queue[head], &data->reached_coins,
		&data->reached_exit);
	explore_neighbors(m, data->queue[head], ctx);
}

static int	run_pathfinding_algorithm(t_map *m, t_pathfinding_data *data)
{
	int				head;
	int				tail;
	t_neighbors_ctx	ctx;

	head = 0;
	tail = 0;
	data->reached_coins = 0;
	data->reached_exit = 0;
	data->queue[tail].x = m->px;
	data->queue[tail].y = m->py;
	(tail)++;
	data->visited[m->py * m->w + m->px] = 1;
	ctx.visited = data->visited;
	ctx.queue = data->queue;
	ctx.tail = &tail;
	while (head < tail)
	{
		process_head(m, data, &ctx, head);
		head++;
	}
	return (1);
}

/* init_pathfinding_loop removed; initialization in run_pathfinding_algorithm */

static int	validate_pathfinding_results(t_map *m, int reached_coins,
		int reached_exit)
{
	if (reached_coins != m->count_c)
	{
		print_error("No se alcanzan todos los C");
		return (0);
	}
	if (!reached_exit)
	{
		print_error("No se alcanza la E");
		return (0);
	}
	return (1);
}

int	check_path(t_map *m)
{
	t_pathfinding_data	data;
	int					total;

	if (!init_pathfinding_data(m, &data.visited, &data.queue, &total))
		return (0);
	run_pathfinding_algorithm(m, &data);
	free(data.queue);
	free(data.visited);
	return (validate_pathfinding_results(m, data.reached_coins,
			data.reached_exit));
}
