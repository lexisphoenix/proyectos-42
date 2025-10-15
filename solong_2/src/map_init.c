/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:40:42 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

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

int	handle_file_operations(const char *path, t_map_read_ctx *ctx)
{
	ctx->fd = open(path, O_RDONLY);
	if (ctx->fd < 0)
		return (0);
	ctx->lines = NULL;
	ctx->cap = 0;
	ctx->len = 0;
	if (!read_map_lines(ctx->fd, &ctx->lines, &ctx->cap, &ctx->len))
	{
		close(ctx->fd);
		free_map(NULL);
		return (0);
	}
	close(ctx->fd);
	return (1);
}

int	validate_and_init_map(t_map *m, char **lines, int len)
{
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
