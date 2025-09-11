/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear_window.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 15:22:24 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_clear_window.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Thu Sep  7 19:46:15 2000 Charlie Root
** Last update Tue Sep 25 17:11:19 2001 Charlie Root
*/



#include	"mlx_int.h"


int		mlx_clear_window(t_xvar *xvar,t_win_list *win)
{
  XClearWindow(xvar->display,win->window);
  if (xvar->do_flush)
    XFlush(xvar->display);
}
