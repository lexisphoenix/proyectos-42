/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/15 18:57:13 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd);

int	parse_map(const char *path, t_map *m)
{
	t_map_read_ctx	ctx;

	if (!handle_file_operations(path, &ctx))
		return (0);
	return (validate_and_init_map(m, ctx.lines, ctx.len));
}

void	free_map(t_map *m)
{
	int	y;

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
