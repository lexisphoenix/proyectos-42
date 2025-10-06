/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:31:21 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:44:02 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

size_t	slen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	putstr(int fd, const char *s)
{
	if (s)
		write(fd, s, slen(s));
}

int	has_ber_ext(const char *s)
{
	size_t	n;

	n = slen(s);
	if (n >= 4 && s[n - 4] == '.'
		&& s[n - 3] == 'b'
		&& s[n - 2] == 'e'
		&& s[n - 1] == 'r')
		return (1);
	return (0);
}
