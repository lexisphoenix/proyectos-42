#ifndef GAME_H
# define GAME_H
# include "map.h"
# include "mlx.h"

typedef struct s_game {
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int   bpp;
	int   sl;
	int   endian;
	int   ts;      // tamaño del tile en px
	int   w, h;    // ancho/alto en tiles
	char **grid;   // mapa
	int px, py;        // posición del jugador
	int remaining_c;   // coleccionables por recoger
	int moves;         // contador de movimientos
	void *img_wall, *img_floor, *img_exit, *img_player;
	int   tx, ty; // tamaño real cargado del xpm
	void *img_player_iz[4];  // mono1iz, mono2iz, mono3iz, mono4iz
	void *img_player_der[4]; // mono1der, mono2der, mono3der, mono4der
    int   player_frame;      // frame actual (0-2)
    int   dir;               // 0=izquierda, 1=derecha
	void *img_coin[2];   // frames de la moneda
    int   coin_frame;    // frame actual
    int   coin_tick;     // contador para cambiar de frame
	int exit_tick; //contador blackhole
	int exit_flip; // 0 = normal, 1 = flipped
	void *img_exit_flipped;
	int idle_tick;       // contador de inactividad
	int idle_state;      // 0 = activo, 1 = en reposo

} t_game;

int  game_start(t_map *m);
#endif
