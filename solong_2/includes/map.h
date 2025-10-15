/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 19:35:22 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include <stddef.h>

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
	int		remaining_c;
}	t_map;

typedef struct s_queue
{
	int	x;
	int	y;
}	t_queue;

typedef struct s_neighbors_ctx
{
	unsigned char	*visited;
	t_queue			*queue;
	int				*tail;
}	t_neighbors_ctx;

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

typedef struct s_map_read_ctx
{
	int		fd;
	char	**lines;
	int		cap;
	int		len;
}	t_map_read_ctx;

/* map_lines.c */
int		read_map_lines(int fd, char ***lines, int *cap, int *len);
size_t	ft_strlen_custom(const char *s);
int		is_whitespace(char c);
char	*strip_newline(char *s);

/* map_init.c */
int		handle_file_operations(const char *path, t_map_read_ctx *ctx);
int		validate_and_init_map(t_map *m, char **lines, int len);

/* map_parser.c */
int		parse_map(const char *path, t_map *m);
void	free_map(t_map *m);

/* map_validation.c */
int		is_rectangular(t_map *m);
int		closed_by_walls(t_map *m);
int		validate_characters_and_counts(t_map *m);
int		check_path(t_map *m);

/* pathfinding */
void	explore_neighbors(t_map *m, t_queue current, t_neighbors_ctx *ctx);

#endif
