/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:12:16 by anieto-m          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* int	main(void)
{
	int		fd;
	char	*line;
	int		i;
	//fd = open("1char.txt", O_RDONLY);
	fd = open("probar2.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) && i < 14)
	{
		printf("Line %d:%s", i + 1, line);
		free(line);
		i++;
	}
	i = 7;
	while (i--)
	{
		line = get_next_line(fd);
		printf("Line :%s", line);
		free(line);
		close(fd);
		return (0);
}*/


char	*get_next_line(int fd); // Prototipo de tu función

int main(void)
{
	int fd;
	char *line;

	// Abrir archivo en modo lectura
	fd = open("/tests/test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	// Leer línea por línea
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); // get_next_line ya devuelve con '\n'
		free(line); // Liberar cada línea
	}

	// Cerrar archivo
	close(fd);
	return (0);
}