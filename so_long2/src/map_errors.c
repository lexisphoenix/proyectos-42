/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:38:02 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/29 12:38:09 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <unistd.h>

void	err(const char *m)
{
	write(2, "Error\n", 6);
	write(2, m, slen(m));
	write(2, "\n", 1);
}

int	validate_counts(int cP, int cC, int cE, t_map *m)
{
	if (cP != 1)
		return (err("Debe haber exactamente 1 P"), 0);
	if (cC < 1)
		return (err("Debe haber al menos 1 C"), 0);
	if (cE < 1)
		return (err("Debe haber al menos 1 E"), 0);
	m->count_p = cP;
	m->count_c = cC;
	m->count_e = cE;
	return (1);
}
