/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   map_pathfinding.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: anieto-m <anieto-m@student.42malaga.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/11 15:22:24 by anieto-m		  #+#	#+#			 */
/*   Updated: 2025/09/18 13:11:34 by anieto-m		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/map.h"
#include <stdlib.h>
#include <unistd.h>

extern int		in_bounds(t_map *m, int x, int y);
extern void		print_error(const char *message);
extern int		init_pathfinding_data(t_map *m, unsigned char **visited,
			t_queue **queue, int *total);
extern void		process_cell(t_map *m, t_queue current, int *reached_coins,
			int *reached_exit);
extern void		explore_neighbors(t_map *m, t_queue current, unsigned char *visited,
			t_queue *queue, int *tail);

static int	run_pathfinding_algorithm(t_map *m, unsigned char *visited,
		t_queue *queue, int *reached_coins, int *reached_exit)
{
	int	head;
	int	tail;

	head = 0;
	tail = 0;
	*reached_coins = 0;
	*reached_exit = 0;
	queue[tail].x = m->px;
	queue[tail].y = m->py;
	tail++;
	visited[m->py * m->w + m->px] = 1;
	while (head < tail)
	{
		process_cell(m, queue[head], reached_coins, reached_exit);
		explore_neighbors(m, queue[head], visited, queue, &tail);
		head++;
	}
	return (1);
}

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
	unsigned char	*visited;
	t_queue			*queue;
	int				total;
	int				reached_coins;
	int				reached_exit;

	if (!init_pathfinding_data(m, &visited, &queue, &total))
		return (0);
	run_pathfinding_algorithm(m, visited, queue, &reached_coins, &reached_exit);
	free(queue);
	free(visited);
	return (validate_pathfinding_results(m, reached_coins, reached_exit));
}
