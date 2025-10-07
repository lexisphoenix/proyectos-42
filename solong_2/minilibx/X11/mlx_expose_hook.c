/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_expose_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 12:03:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/10/07 16:49:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_expose_hook.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Thu Aug  3 11:49:06 2000 Charlie Root
** Last update Fri Feb 23 17:07:42 2001 Charlie Root
*/


#include	"mlx_int.h"




int		mlx_expose_hook(t_win_list *win,int (*funct)(),void *param)
{
  win->hooks[Expose].hook = funct;
  win->hooks[Expose].param = param;
  win->hooks[Expose].mask = ExposureMask;
}
