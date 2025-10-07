/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_anti_resize_win.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int_anti_resize_win.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Tue Aug  8 14:31:05 2000 Charlie Root
** Last update Tue Sep 25 15:56:58 2001 Charlie Root
*/

#include	"mlx_int.h"


int	mlx_int_anti_resize_win(t_xvar *xvar,Window win,int w,int h)
{
  XSizeHints    hints;
  long		toto;
  
  XGetWMNormalHints(xvar->display,win,&hints,&toto);
  hints.width = w;
  hints.height = h;
  hints.min_width = w;
  hints.min_height = h;
  hints.max_width = w;
  hints.max_height = h;
  hints.flags = PPosition | PSize | PMinSize | PMaxSize;
  XSetWMNormalHints(xvar->display,win,&hints);
}
