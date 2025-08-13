/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m  <anieto-m@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 14:51:56 by anieto-m          #+#    #+#             */
/*   Updated: 2025/08/12 16:08:26 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
int main(void)
{
	int len1 = ft_printf("Mi número es: %d y en hex: %x\n", 42, 42);
	int len2 = printf("Mi número es: %d y en hex: %x\n", 42, 42);
	ft_printf("Longitud ft_printf: %d\n", len1);
	printf("Longitud printf: %d\n", len2);
}

