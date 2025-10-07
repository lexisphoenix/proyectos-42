/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
*	DESCRIPTION
*	Adds the element ’new’ at the beginning of the list.
*	PARAMETERS
*	#1. The address of a pointer to the first link of a list.
*	#2. The address of a pointer to the element to be added to the list.
*	RETURN VALUES
*	-
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new)
	{
		if (!lst)
			*lst = new;
		new->next = *lst;
		*lst = new;
	}
}
