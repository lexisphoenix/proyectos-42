/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 13:11:34 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <stdlib.h>
#include <unistd.h>

typedef struct s_queue
{
    int x;
    int y;
}   t_queue;

static int	in_bounds(t_map *m, int x, int y)
{
    if (x >= 0 && x < m->w && y >= 0 && y < m->h)
        return (1);
    return (0);
}

static void	print_error(const char *message)
{
    write(2, "Error\n", 6);
    write(2, message, 50);
    write(2, "\n", 1);
}

int	check_path(t_map *m)
{
    int             total;
    unsigned char   *visited;
    t_queue         *queue;
    int             head;
    int             tail;
    int             reached_coins;
    int             reached_exit;
    int             dirs[4][2];
    int             i;

    total = m->w * m->h;
    visited = calloc(total, 1);
    queue = malloc(sizeof(t_queue) * total);
    if (!visited || !queue)
    {
        free(visited);
        free(queue);
        print_error("Memoria (path)");
        return (0);
    }
    head = 0;
    tail = 0;
    reached_coins = 0;
    reached_exit = 0;
    queue[tail].x = m->px;
    queue[tail].y = m->py;
    tail++;
    visited[m->py * m->w + m->px] = 1;
    dirs[0][0] = 1;
    dirs[0][1] = 0;
    dirs[1][0] = -1;
    dirs[1][1] = 0;
    dirs[2][0] = 0;
    dirs[2][1] = 1;
    dirs[3][0] = 0;
    dirs[3][1] = -1;
    while (head < tail)
    {
        t_queue current;
        char    cell;
        int     nx;
        int     ny;
        char    ncell;
        int     idx;

        current = queue[head];
        head++;
        cell = m->grid[current.y][current.x];
        if (cell == 'C')
            reached_coins++;
        if (cell == 'E')
            reached_exit = 1;
        i = 0;
        while (i < 4)
        {
            nx = current.x + dirs[i][0];
            ny = current.y + dirs[i][1];
            if (in_bounds(m, nx, ny))
            {
                ncell = m->grid[ny][nx];
                if (ncell != '1')
                {
                    idx = ny * m->w + nx;
                    if (!visited[idx])
                    {
                        visited[idx] = 1;
                        queue[tail].x = nx;
                        queue[tail].y = ny;
                        tail++;
                    }
                }
            }
            i++;
        }
    }
    free(queue);
    free(visited);
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
