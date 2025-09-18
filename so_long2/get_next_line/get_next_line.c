/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 15:11:14 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*first_line(char *rest) //
{
	int		i;
	int		j;
	char	*line;

	if (!rest || rest[0] == '\0')
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (rest[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = rest[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*keep_next_line(char *rest)
{
	int		i;
	int		j;
	char	*line;

	if (!rest)
		return (NULL);
	i = 0;
	while (rest[i] && rest[i] != '\n')
		i++;
	if (!rest[i])
	{
		free(rest);
		return (NULL);
	}
	i++;
	line = malloc(ft_strlen(rest + i) + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (rest[i])
		line[j++] = rest[i++];
	line[j] = '\0';
	free(rest);
	return (line);
}

static int	read_until_line(int fd, char **rest, char *buffer) //
{
	ssize_t	n;
	char	*tmp;

	n = 1;
	while (!jump_line(*rest) && n > 0)
	{
		n = read(fd, buffer, BUFFER_SIZE);
		if (n == -1)
		{
			free(*rest);
			*rest = NULL;
			return (0);
		}
		buffer[n] = '\0';
		tmp = join_and_free(*rest, buffer);
		if (!tmp)
		{
			free(*rest);
			*rest = NULL;
			return (0);
		}
		*rest = tmp;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!read_until_line(fd, &rest, buffer))
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	line = first_line(rest);
	rest = keep_next_line(rest);
	return (line);
}

/* #include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	fd1 = open("test1.txt", O_RDONLY);
	fd2 = open("test2.txt", O_RDONLY);
	if (fd1 < 0 || fd2 < 0)
		return (1);
	line1 = get_next_line(fd1);
	printf("fd1: %s", line1);
	free(line1);

	line2 = get_next_line(fd2);
	printf("fd2: %s", line2);
	free(line2);
	close(fd1);
	close(fd2);
	return (0);
} */