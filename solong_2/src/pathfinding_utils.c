/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   pathfinding_utils.c							   :+:	  :+:	:+:   */
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

extern void		print_error(const char *message);

int	in_bounds(t_map *m, int x, int y)
{
	if (x >= 0 && x < m->w && y >= 0 && y < m->h)
		return (1);
	return (0);
}

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

void	check_neighbor(t_map *m, t_queue current, unsigned char *visited,
		t_queue *queue, int *tail, int dx, int dy)
{
	int	nx;
	int	ny;
	int	idx;

	nx = current.x + dx;
	ny = current.y + dy;
	if (in_bounds(m, nx, ny) && m->grid[ny][nx] != '1')
	{
		idx = ny * m->w + nx;
		if (!visited[idx])
		{
			visited[idx] = 1;
			queue[*tail].x = nx;
			queue[*tail].y = ny;
			(*tail)++;
		}
	}
}

void	explore_neighbors(t_map *m, t_queue current, unsigned char *visited,
		t_queue *queue, int *tail)
{
	int	dirs[4][2];
	int	i;

	init_directions(dirs);
	i = 0;
	while (i < 4)
	{
		check_neighbor(m, current, visited, queue, tail,
			dirs[i][0], dirs[i][1]);
		i++;
	}
}
