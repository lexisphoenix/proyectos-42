/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   map_utils.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: anieto-m <anieto-m@student.42malaga.com	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/09/11 15:22:24 by anieto-m		  #+#	#+#			 */
/*   Updated: 2025/09/18 13:11:34 by anieto-m		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../includes/map.h"
#include <unistd.h>

size_t	ft_strlen_custom(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

void	print_error(const char *message)
{
	write(2, "Error\n", 6);
	write(2, message, ft_strlen_custom(message));
	write(2, "\n", 1);
}
