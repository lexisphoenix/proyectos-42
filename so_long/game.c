#include "game.h"
#include <stdlib.h>
#include <stdio.h>    // para snprintf/printf
#include <unistd.h>   // para write()

// static unsigned int rgb(int r,int g,int b){ return ((r&255)<<16)|((g&255)<<8)|(b&255); }
// static void rect_border(t_game *g, int x, int y, int w, int h, unsigned int c);

// static void px(t_game *g, int x, int y, unsigned int c){
// 	if (x<0 || y<0 || x>=g->w*g->ts || y>=g->h*g->ts) return;
// 	*(unsigned int *)(g->addr + y * g->sl + x * (g->bpp/8)) = c;
// }

// static void rect(t_game *g, int x, int y, int w, int h, unsigned int c){
// 	for (int j=0;j<h;j++) for (int i=0;i<w;i++) px(g, x+i, y+j, c);
// }

// static void render(t_game *g){
// 	for (int y=0; y<g->h; y++){
// 		for (int x=0; x<g->w; x++){
// 			char t = g->grid[y][x];
// 			unsigned int base = rgb(20,20,20);      // '0'
// 			if (t=='1') base = rgb(90,90,90);       // muro
// 			else if (t=='C') base = rgb(230,190,40);// coleccionable
// 			else if (t=='E') base = rgb(60,160,60); // salida
// 			else if (t=='P') base = rgb(60,120,200);// jugador
// 			rect(g, x*g->ts, y*g->ts, g->ts, g->ts, base);               // <- pinta el tile
// 			rect_border(g, x*g->ts, y*g->ts, g->ts, g->ts, rgb(0,0,0));  // <- borde opcional	
// 		}
// 	}
// 	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
// }

#ifndef ASSETS_DIR
# define ASSETS_DIR "assets"
#endif

static void *load_img(t_game *g, const char *file){
    char path[512];
    snprintf(path, sizeof(path), "%s/%s", ASSETS_DIR, file);
    void *img = mlx_xpm_file_to_image(g->mlx, path, &g->tx, &g->ty);
    fprintf(stderr, "load '%s' -> %p (%dx%d)\n", path, img, g->tx, g->ty);
	fprintf(stderr,"loading: %s\n", path);

    return img;
}

// static void render(t_game *g){
// 	mlx_clear_window(g->mlx, g->win);
// 	for (int y=0; y<g->h; y++){
//         for (int x=0; x<g->w; x++){
//             void *tile = g->img_floor;
//             char t = g->grid[y][x];
//             if (t=='1') tile = g->img_wall;
//             else if (t=='C') tile = g->img_coin;
//             else if (t=='E') tile = g->img_exit;
//             else if (t=='P') tile = g->img_player;
//             if (tile) mlx_put_image_to_window(g->mlx, g->win, tile, x*g->ts, y*g->ts);
// 		}
// 	}
// 	mlx_string_put(g->mlx, g->win, 8, 14, 0xFFFFFF, "render ok");

// }
// CHATGPT
// static void render(t_game *g){
//     // NO limpiar mientras depuras
//     // mlx_clear_window(g->mlx, g->win);

//     // 2.1) dibuja SIEMPRE un tile en 0,0; si esto no aparece, la imagen es NULL o corrupta
//     if (g->img_floor) mlx_put_image_to_window(g->mlx, g->win, g->img_floor, 0, 0);

//     // 2.2) recorre el grid y cuenta cuántos dibuja
//     int drawn = 0;
//     for (int y=0; y<g->h; y++){
//         for (int x=0; x<g->w; x++){
//             void *tile = g->img_floor;
//             char t = g->grid[y][x];
//             if (t=='1') tile = g->img_wall;
//             else if (t=='C') tile = g->img_coin;
//             else if (t=='E') tile = g->img_exit;
//             else if (t=='P') tile = g->img_player;
//             if (tile){ mlx_put_image_to_window(g->mlx, g->win, tile, x*g->ts, y*g->ts); drawn++; }
//         }
//     }
//     // marca visual
//     mlx_string_put(g->mlx, g->win, 8, 14, 0xFFFFFF, "render ok");

//     // log a stderr para verificar
//     fprintf(stderr, "tiles dibujados: %d (ts=%d, w=%d, h=%d)\n", drawn, g->ts, g->w, g->h);
// }

static void render(t_game *g){
    mlx_clear_window(g->mlx, g->win); // Limpia ventana completa

    for (int y=0; y<g->h; y++){
        for (int x=0; x<g->w; x++){
            char t = g->grid[y][x];
            void *tile = g->img_floor; // fondo por defecto

            if (t == '1')      tile = g->img_wall;
            // else if (t == 'C') tile = g->img_coin;
			else if (t == 'C') 
    			tile = g->img_coin[g->coin_frame];

            else if (t == 'E') tile = g->img_exit;
            //else if (t == 'P') tile = g->img_player;
			else if (t == 'E') {
		    	if (g->exit_flip == 0)
		        	tile = g->img_exit;
		    	else
	        		tile = g->img_exit_flipped; // <- misma imagen pero espejada
			}
			else if (t == 'P') {
				if (g->idle_state) {
					if (g->dir == 0)
						tile = g->img_player_iz[3]; // mono4iz.xpm
					else
						tile = g->img_player_der[3]; // mono4der.xpm
				} else {
					if (g->dir == 0)
						tile = g->img_player_iz[g->player_frame];
					else
						tile = g->img_player_der[g->player_frame];
				}
			}
            mlx_put_image_to_window(g->mlx, g->win, g->img_floor, x*g->ts, y*g->ts);
            mlx_put_image_to_window(g->mlx, g->win, tile, x*g->ts, y*g->ts);
        }
    }
}
static int on_expose(t_game *g){ render(g); return 0; }

// static int loop_anim(t_game *g)
// {
// 	const int delay = 45; // ajusta a gusto
// 	if (g->coin_tick++ >= delay) 
// 		{
//     		g->coin_tick = 0;
//     		g->coin_frame = (g->coin_frame + 1) % 2;
//     		render(g);
// 		}
//     return (0);
// }


// bucle de animaciones
static int loop_anim(t_game *g)
{
    // monedas
    const int coin_delay = 60;
    g->coin_tick++;
    if (g->coin_tick >= coin_delay) {
        g->coin_tick = 0;
        g->coin_frame = (g->coin_frame + 1) % 2;
    }

    // reposo del mono
    g->idle_tick++;
    if (g->idle_tick > 300) { // tras ~5s sin moverse (60*5 = 300)
        g->idle_state = 1;
    }

    render(g);
    return 0;
}

static int try_move(t_game *g, int dx, int dy){
	int nx = g->px + dx;
	int ny = g->py + dy;
	if (nx < 0 || nx >= g->w || ny < 0 || ny >= g->h) return 0;

	char dest = g->grid[ny][nx];
	if (dest == '1') return 0; // muro

	if (dest == 'C') g->remaining_c--;

	if (dest == 'E') {
		if (g->remaining_c == 0) {
			// WINNNN!
			write(1, "You win\n", 8);
			mlx_destroy_window(g->mlx, g->win);
			exit(0);
		} else {
			return 0; // no puedes salir aún
		}
	}

	// mover jugador
	g->grid[g->py][g->px] = '0';
	g->grid[ny][nx] = 'P';
	g->px = nx; g->py = ny;
	g->moves++;

	if (dx < 0) g->dir = 0; // izquierda
	if (dx > 0) g->dir = 1; // derecha

	// ciclo de frames
	g->player_frame++;
	if (g->player_frame > 2) g->player_frame = 0;


	// feedback
	char buf[64];
	int n = snprintf(buf, sizeof(buf), "Moves: %d, C left: %d\n", g->moves, g->remaining_c);
	write(1, buf, n);

	// repintar
	render(g);
	return 1;
}


// static int on_key(int key, t_game *g){
// 	(void)g;
// 	if (key==53 /*ESC macOS*/ || key==65307 /*ESC X11*/){
// 		mlx_destroy_window(g->mlx, g->win);
// 		exit(0);
// 	}
// 	return 0;
// }

static int on_key(int key, t_game *g){
	int dx = 0; 
	int	dy = 0;

	if (key==53 || key==65307) { // ESC
		mlx_destroy_window(g->mlx, g->win);
		exit(0);
	}
	// macOS: W(13) A(0) S(1) D(2) | flechas: 123-126
	if (key==13 || key==126) dy = -1;      // W / ↑
	else if (key==1 || key==125) dy = 1;   // S / ↓
	else if (key==0 || key==123) dx = -1;  // A / ←
	else if (key==2 || key==124) dx = 1;   // D / →
	// intenta mover
	//if (dx || dy) try_move(g, dx, dy);
	if (dx || dy) {
    	try_move(g, dx, dy);
    	g->idle_tick = 0;
    	g->idle_state = 0;
	}
	return 0;
}

static int on_close(t_game *g){
	mlx_destroy_window(g->mlx, g->win);
	exit(0);
	return 0;
}

// int game_start(t_map *m){
//     t_game g;

//     g.ts = 64;                    // tamaño del tile
//     g.w = m->w; g.h = m->h;
// 	g.grid = m->grid;

// 	g.px = m->px; 
// 	g.py = m->py;
// 	g.remaining_c = m->count_c;
// 	g.moves = 0;
// 	// inicializar MLX
//     g.mlx = mlx_init();
// 	// if (!g.mlx) return 0;
// 	// cargar imágenes
// 	if (!g.mlx) return 0;

// 	g.img_floor  = load_img(&g, "floor.xpm");
// 	if (!g.img_floor){ fprintf(stderr,"no floor.xpm\n"); return 0; }
// 	g.img_wall   = load_img(&g, "wall.xpm");
// 	g.img_coin   = load_img(&g, "coin.xpm");
// 	g.img_exit   = load_img(&g, "exit.xpm");
// 	g.img_player = load_img(&g, "player.xpm");
// 	// comprobar carga correcta
// 	if (!g.img_floor || !g.img_wall || !g.img_coin || !g.img_exit || !g.img_player)
//     	return 0;
//    	g.ts = g.tx;
// 	// crear ventana e imagen
//     g.win = mlx_new_window(g.mlx, g.w*g.ts, g.h*g.ts, "so_long");
//     g.img = mlx_new_image(g.mlx, g.w*g.ts, g.h*g.ts);
//     g.addr = mlx_get_data_addr(g.img, &g.bpp, &g.sl, &g.endian);

//     // Debug correcto aquí (sí existe 'g')
//     printf("win %dx%d, tile=%d, bpp=%d, sl=%d, endian=%d\n",
//            g.w*g.ts, g.h*g.ts, g.ts, g.bpp, g.sl, g.endian);

//     render(&g);
// 	mlx_hook(g.win, 17, 0, (int (*)(void*))on_close, &g);
// 	mlx_key_hook(g.win, (int (*)(int, void*))on_key, &g);
// 	mlx_loop(g.mlx);
	
// 	mlx_destroy_image(g.mlx, g.img_wall);
// 	mlx_destroy_image(g.mlx, g.img_floor);
// 	mlx_destroy_image(g.mlx, g.img_coin);
// 	mlx_destroy_image(g.mlx, g.img_exit);
// 	mlx_destroy_image(g.mlx, g.img_player);



// 	mlx_destroy_image(g.mlx, g.img);
// 	// en macOS, mlx se libera internamente al cerrar ventana
// 	return 1;
// }

int game_start(t_map *m){
    t_game g;

	 g.ts = 64;  
    // datos del mapa
    g.w = m->w; g.h = m->h;
    g.grid = m->grid;
    g.px = m->px; g.py = m->py;
    g.remaining_c = m->count_c;
    g.moves = 0;

    // 1) inicializa MLX
    g.mlx = mlx_init();
    if (!g.mlx) return 0;

    // 2) carga sprites (usa tu load_img si lo tienes)
    g.img_floor  = load_img(&g, "floor.xpm");
    if (!g.img_floor) return 0; // corta pronto para ver el primer fallo
	fprintf(stderr, "floor %p %dx%d\n", (void*)g.img_floor, g.tx, g.ty);
	g.img_wall   = load_img(&g, "wall.xpm");
	fprintf(stderr, "wall  %p %dx%d\n", (void*)g.img_wall, g.tx, g.ty);
	g.img_coin[0] = load_img(&g, "up/up1.xpm");
	g.img_coin[1] = load_img(&g, "up/up2.xpm");
	fprintf(stderr, "coin  %p %dx%d\n", (void*)g.img_coin, g.tx, g.ty);
	g.img_exit   = load_img(&g, "exit.xpm");
	fprintf(stderr, "exit  %p %dx%d\n", (void*)g.img_exit, g.tx, g.ty);
	g.img_player = load_img(&g, "player.xpm");
	fprintf(stderr, "player%p %dx%d\n", (void*)g.img_player, g.tx, g.ty);
	g.img_player_iz[3] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono4iz.xpm", &g.tx, &g.ty);
	g.img_player_der[3] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono4der.xpm", &g.tx, &g.ty);
    //if (!g.img_wall || !g.img_coin || !g.img_exit || !g.img_player) return 0;
	if (!g.img_wall || !g.img_coin[0] || !g.img_coin[1] ||
    !g.img_exit || !g.img_player)
    return 0;
    // 3) ajusta tamaño de tile al del XPM (p.ej. 16 si tus XPM de prueba son 16x16)
    //g.ts = g.tx;
	//ANIMACIONES
	g.img_player_iz[0] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono1iz.xpm", &g.tx, &g.ty);
	g.img_player_iz[1] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono2iz.xpm", &g.tx, &g.ty);
	g.img_player_iz[2] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono3iz.xpm", &g.tx, &g.ty);

	g.img_player_der[0] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono1der.xpm", &g.tx, &g.ty);
	g.img_player_der[1] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono2der.xpm", &g.tx, &g.ty);
	g.img_player_der[2] = mlx_xpm_file_to_image(g.mlx, "assets/player/mono3der.xpm", &g.tx, &g.ty);

	g.player_frame = 0;
	g.dir = 0; // por defecto, mirando a la izquierda

	//MONEDA
	g.img_coin[0] = mlx_xpm_file_to_image(g.mlx, "assets/up/up1.xpm", &g.tx, &g.ty);
	g.img_coin[1] = mlx_xpm_file_to_image(g.mlx, "assets/up/up2.xpm", &g.tx, &g.ty);

	g.coin_frame = 0;
	g.coin_tick = 0;


    // 4) crea ventana (después de conocer g.ts)
    //g.win = mlx_new_window(g.mlx, g.w*g.ts, g.h*g.ts, "so_long");
	g.win = mlx_new_window(g.mlx, g.w * g.ts, g.h * g.ts, "so_long");

    // 5) (opcional) framebuffer si lo usas; no es necesario para put_image_to_window
    // g.img  = mlx_new_image(g.mlx, g.w*g.ts, g.h*g.ts);
    // g.addr = mlx_get_data_addr(g.img, &g.bpp, &g.sl, &g.endian);

    // 6) pinta una vez y registra hooks
    render(&g);
    mlx_expose_hook(g.win, (int (*)(void*))on_expose, &g);      // repinta al exponerse
    mlx_key_hook(g.win, (int (*)(int, void*))on_key, &g);       // teclado
    mlx_hook(g.win, 17, 0, (int (*)(void*))on_close, &g);       // botón cerrar

    // 7) loop
	mlx_loop_hook(g.mlx, (int (*)(void *))loop_anim, &g);
    mlx_loop(g.mlx);

    // destrucción de imágenes si llegas aquí
    mlx_destroy_image(g.mlx, g.img_floor);
    mlx_destroy_image(g.mlx, g.img_wall);
    mlx_destroy_image(g.mlx, g.img_coin);
    mlx_destroy_image(g.mlx, g.img_exit);
    mlx_destroy_image(g.mlx, g.img_player);
    return 1;
}

// static void rect_border(t_game *g, int x, int y, int w, int h, unsigned int c){
//     for (int i=0;i<w;i++){ px(g,x+i,y,c); px(g,x+i,y+h-1,c); }
//     for (int j=0;j<h;j++){ px(g,x,y+j,c); px(g,x+w-1,y+j,c); }
// }


