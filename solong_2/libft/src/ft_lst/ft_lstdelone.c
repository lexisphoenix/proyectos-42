/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	DESCRIPTION
*	Takes as a parameter an element and frees the memory of the element’s 
*	content using the function ’del’ given as a parameter and free the element.
*	The memory of ’next’ must not be freed.
*	PARAMETERS
*	#1. The element to free.
*	#2. The address of the function used to delete the content.
*	RETURN VALUES
*	-
*/

#include "libft.h"
#include <stdlib.h>

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		del(lst->content);
		free(lst);
	}
}
