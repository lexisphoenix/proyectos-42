/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:35:16 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
    char    **grid;
    int     w;
    int     h;
    int     px;
    int     py;
    int     count_p;
    int     count_c;
    int     count_e;
}   t_map;

typedef struct s_queue
{
    int x;
    int y;
}   t_queue;

int     parse_map(const char *path, t_map *m);
void    free_map(t_map *m);
int     is_rectangular(t_map *m);
int     closed_by_walls(t_map *m);
int     validate_characters_and_counts(t_map *m);
int     check_path(t_map *m);

#endif
