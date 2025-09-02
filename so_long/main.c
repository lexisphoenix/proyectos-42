#include "map.h"
#include <unistd.h>
#include "game.h"
#include <stdio.h>

static size_t	slen(const char *s){ size_t i=0; while(s && s[i]) i++; return i; }
// helper para obtener la longitud de una cadena C (número de caracteres antes del '\0')
static void	putstr(int fd, const char *s){ if(s) write(fd, s, slen(s)); }
// función auxiliar para imprimir cadenas a un descriptor de archivo (1=stdout, 2=stderr)
static int has_ber_ext(const char *s){
	size_t n = slen(s);
	return (n>=4 && s[n-4]=='.' && s[n-3]=='b' && s[n-2]=='e' && s[n-1]=='r');
}
// función auxiliar para verificar que el nombre del archivo termina en ".ber" (para mapas de "so_long")
int	main(int argc, char **argv){
	if (argc != 2){ putstr(2, "Uso: ./check map.ber\n"); return 1; }
	if (!has_ber_ext(argv[1])){ putstr(2,"Error: extensión debe ser .ber\n"); return 1; }
	// cargar el mapa y validar su formato básico (anchura, altura, rectangular)
	t_map m = {0};
	if (!parse_map(argv[1], &m)){
		putstr(2, "Error al cargar el mapa\n");
		return 1;
	}
	char buf[64];
	int n = snprintf(buf, sizeof(buf), "map %dx%d\n", m.w, m.h);
	write(1, buf, n);
	// en vez de imprimir texto, abre la ventana:
	if (!game_start(&m)){ putstr(2, "Error al iniciar MLX\n"); free_map(&m); return 1; }
	// ... aquí podrías añadir más validaciones específicas del mapa
	// liberar memoria y salir
	// Demostración: imprime el mapa cargado
	for (int y=0; y<m.h; y++){ putstr(1, m.grid[y]); putstr(1, "\n"); }
	free_map(&m);
	return 0;
}
//Este es un main de prueba para verificar que el parser de mapas funciona correctamente y que no hay fugas de memoria.