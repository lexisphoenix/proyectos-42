/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 19:16:29 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map {
    char **grid;
    int   w;
    int   h;
    int   px; // se usará más adelante
    int   py; // se usará más adelante
    int   count_p, count_c, count_e; // se usarán más adelante
} t_map;

int  parse_map(const char *path, t_map *m);
void free_map(t_map *m);

#endif
