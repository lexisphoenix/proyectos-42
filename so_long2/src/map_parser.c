/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:41:12 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char			*get_next_line(int fd);
void			free_map(t_map *m);

// --- PROTOTIPOS DE VALIDACIÓN ---
static int		is_rectangular(t_map *m);
static int		closed_by_walls(t_map *m);
static int		chars_and_counts(t_map *m);
static int		check_path(t_map *m);
static int		push_line(char ***arr, int *cap, int *len, char *line);

// --- PARSE MAP ---
static int	read_map_lines(const char *path, char ***lines, int *len)
{
	int		fd;
	int		cap;
	char	*raw;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	*lines = NULL;
	cap = 0;
	*len = 0;
	raw = get_next_line(fd);
	while (raw)
	{
		raw = strip_nl(raw);
		if (!raw || !push_line(lines, &cap, len, raw))
			return (close(fd), free(*lines), 0);
		raw = get_next_line(fd);
	}
	close(fd);
	if (*len == 0)
		return (free(*lines), 0);
	return (1);
}


static void	init_map_struct(t_map *m, char **lines, int len)
{
	m->grid = lines;
	m->h = len;
	m->w = (int)slen(lines[0]);
	m->px = -1;
	m->py = -1;
	m->count_p = 0;
	m->count_c = 0;
	m->count_e = 0;
}

int	parse_map(const char *path, t_map *m)
{
	char	**lines;
	int		len;

	if (!read_map_lines(path, &lines, &len))
		return (0);
	init_map_struct(m, lines, len);
	if (!is_rectangular(m) || !closed_by_walls(m)
		|| !chars_and_counts(m) || !check_path(m))
	{
		free_map(m);
		return (0);
	}
	return (1);
}
