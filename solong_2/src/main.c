/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/11 19:13:23 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <unistd.h>
#include "game.h"
#include "ft_printf.h"

static size_t	slen(const char *s){ size_t i=0; while(s && s[i]) i++; return i; }
// helper para obtener la longitud de una cadena C
static void	putstr(int fd, const char *s){ if(s) write(fd, s, slen(s)); }
// función auxiliar para imprimir cadenas a un fd
static int has_ber_ext(const char *s){
	size_t n = slen(s);
	return (n>=4 && s[n-4]=='.' && s[n-3]=='b' && s[n-2]=='e' && s[n-1]=='r');
}
// verificar que el nombre del archivo es un .ber
int	main(int argc, char **argv){
	if (argc != 2){ putstr(2, "Uso: ./check map.ber\n"); return 1; }
	if (!has_ber_ext(argv[1])){ putstr(2,"Error: extensión debe ser .ber\n"); return 1; }
	// cargar el mapa y validar su formato básico (anchura, altura, rectangular)
	t_map m = {0};
	if (!parse_map(argv[1], &m)){
		putstr(2, "Error al cargar el mapa\n");
		return 1;
	}
	ft_printf("map %dx%d\n", m.w, m.h);
	if (!game_start(&m)){ putstr(2, "Error al iniciar MLX\n"); free_map(&m); return 1; }
	for (int y=0; y<m.h; y++){ putstr(1, m.grid[y]); putstr(1, "\n"); }
	free_map(&m);
	return 0;
}

