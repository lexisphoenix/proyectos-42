/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 19:13:27 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, int c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	if (c == '\0')
		return ((char *)&str[ft_len(str)]);
	while (str[i])
	{
		if (str[i] == (char) c)
			return ((char *)&str[i]);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*out;
	static char	*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		free (str);
		str = NULL;
		return (NULL);
	}
	str = ft_alloc(fd, str);
	if (!str)
		return (NULL);
	out = ft_nline(str);
	str = ft_rline(str);
	return (out);
}

// int main(int ac, char **av)
// {
// 	int		fd;
// 	char	*line;

// 	if (ac == 2)
// 	{
// 		fd = open(av[1], O_RDONLY);
// 		if (fd == -1)
// 			return (1);
// 		line = get_next_line(fd);
// 		while (line)
// 		{
// 			printf("%s\n", line);
// 			free(line);
// 			line = get_next_line(fd);
// 		}
// 		free(line);
// 		close(fd);
// 	}
// 	return (0);
// }
