/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/08 14:52:01 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
	int		px;
	int		py;
	int		count_p;
	int		count_c;
	int		count_e;
}	t_map;

typedef struct s_queue
{
	int	x;
	int	y;
}	t_queue;

typedef struct s_validation_data
{
	int		count_p;
	int		count_c;
	int		count_e;
	t_map	*m;
}	t_validation_data;

typedef struct s_pathfinding_data
{
	unsigned char	*visited;
	t_queue			*queue;
	int				reached_coins;
	int				reached_exit;
}	t_pathfinding_data;

int		parse_map(const char *path, t_map *m);
void	free_map(t_map *m);
int		is_rectangular(t_map *m);
int		closed_by_walls(t_map *m);
int		validate_characters_and_counts(t_map *m);
int		check_path(t_map *m);

#endif
