/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   map_parser.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: anieto-m <anieto-m@student.42malaga.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/11 15:22:24 by anieto-m		  #+#	#+#			 */
/*   Updated: 2025/09/18 13:11:34 by anieto-m		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

static size_t	ft_strlen_custom(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	is_whitespace(char c)
{
	return (c == '\n' || c == '\r' || c == ' ' || c == '\t');
}

static char	*strip_newline(char *s)
{
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen_custom(s);
	while (n && is_whitespace(s[n - 1]))
	{
		n--;
		s[n] = '\0';
	}
	if (n == 0)
	{
		free(s);
		return (NULL);
	}
	return (s);
}

static int	push_line(char ***arr, int *cap, int *len, char *line)
{
	int		new_cap;
	char	**tmp;
	int		i;

	if (*len + 1 >= *cap)
	{
		if (*cap == 0)
			new_cap = 8;
		else
			new_cap = *cap * 2;
		tmp = malloc(sizeof(char *) * new_cap);
		if (!tmp)
			return (0);
		i = 0;
		while (i < *len)
		{
			tmp[i] = (*arr)[i];
			i++;
		}
		free(*arr);
		*arr = tmp;
		*cap = new_cap;
	}
	(*arr)[*len] = line;
	(*len)++;
	(*arr)[*len] = NULL;
	return (1);
}

static int	read_map_lines(int fd, char ***lines, int *cap, int *len)
{
	char	*raw;

	while ((raw = get_next_line(fd)))
	{
		raw = strip_newline(raw);
		if (!raw)
			return (0);
		if (!push_line(lines, cap, len, raw))
			return (0);
	}
	return (1);
}

static void	init_map_struct(t_map *m, char **lines, int len)
{
	m->grid = lines;
	m->h = len;
	m->w = (int)ft_strlen_custom(lines[0]);
	m->px = -1;
	m->py = -1;
	m->count_p = 0;
	m->count_c = 0;
	m->count_e = 0;
}

static int	validate_map(t_map *m)
{
	if (!is_rectangular(m) || !closed_by_walls(m))
		return (0);
	if (!validate_characters_and_counts(m) || !check_path(m))
		return (0);
	return (1);
}

int	parse_map(const char *path, t_map *m)
{
	int		fd;
	char	**lines;
	int		cap;
	int		len;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	lines = NULL;
	cap = 0;
	len = 0;
	if (!read_map_lines(fd, &lines, &cap, &len))
	{
		close(fd);
		free_map(m);
		return (0);
	}
	close(fd);
	if (len == 0)
	{
		free(lines);
		return (0);
	}
	init_map_struct(m, lines, len);
	if (!validate_map(m))
	{
		free_map(m);
		return (0);
	}
	return (1);
}

void	free_map(t_map *m)
{
	int y;

	if (!m || !m->grid)
		return ;
	y = 0;
	while (y < m->h)
	{
		free(m->grid[y]);
		y++;
	}
	free(m->grid);
	m->grid = NULL;
}