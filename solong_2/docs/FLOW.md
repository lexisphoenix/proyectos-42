# Flujo y mapa de llamadas de so_long

Este documento explica el flujo del programa `so_long` (en español) y actúa como guía para entender cómo se conectan las funciones entre sí. Está pensado para alguien que empieza en C: explicaré los pasos, estructuras y un "mapa de llamadas" con flechas.

## Resumen rápido
El programa lee un mapa desde un fichero, lo valida, comprueba que el jugador puede alcanzar todas las monedas y la salida, inicializa la ventana y las texturas con MiniLibX, y entra en el bucle de eventos donde responde a teclado y dibuja el juego.

---

## Estructuras principales (resumen)
- `t_map` (en `includes/map.h`)
  - char **grid; // matriz de filas del mapa
  - int w, h; // ancho y alto
  - int px, py; // posición inicial del jugador
  - int count_c; // cantidad de monedas (C)
  - int count_e; // cantidad de salidas (E)

- `t_game` (en `includes/game.h`)
  - void *mlx; void *win; // punteros MLX
  - void *img_*; // imágenes para wall/floor/player/coins/exit
  - char **grid; int w,h, ts; // referencia al mapa y tile size
  - int px, py; int remaining_c; int moves; // estado runtime

- `t_pathfinding_data` y `t_neighbors_ctx` para BFS interno.

---

## Flujo principal (alto nivel)
1. `main(argc, argv)`
   - comprobar argumentos (ruta del mapa)
   - llamar `parse_map(path, &m)`
   - llamar `game_start(&m)`
2. `parse_map(path, &m)`
   - `handle_file_operations(path, &ctx)` / `read_map_lines(...)` para leer líneas
   - `validate_and_init_map(&m, lines, len)`
     - `init_map_struct()`
     - `validate_map()` &rarr; `is_rectangular`, `closed_by_walls`, `validate_characters_and_counts`
     - `check_path()` (usa BFS)
3. `game_start(&m)`
   - `allocate_game_memory()` -> `t_game *g`
   - `init_map_data(g, &m)`
   - `init_mlx(g)` / `create_window(g)`
   - `texture_loader` carga imágenes
   - `setup_hooks(g)` -> registra `on_key_press`, `on_window_close`, `loop_animation`
   - `mlx_loop(g->mlx)` entra en el bucle de eventos
4. Bucle (MLX internamente):
   - `on_key_press(key, g)` &rarr; `try_move(g, dx, dy)`
   - `loop_animation(g)` &rarr; actualizar frames y `render(g)`
   - `render(g)` dibuja con `mlx_put_image_to_window`

---

## Mapa de llamadas (call graph) — versión textual con flechas
A continuación verás un mapa lo más detallado posible con funciones clave y a quién llaman. Las funciones de librería (MLX) aparecen en mayúsculas.

main
├─> parse_map(path, &m)
│   ├─> handle_file_operations(path, &ctx)
│   │   └─> read_map_lines(fd, &lines, &cap, &len)
│   │       └─> get_next_line(fd)
│   └─> validate_and_init_map(&m, lines, len)
│       ├─> init_map_struct(m, lines, len)
│       └─> validate_map(m)
│           ├─> is_rectangular(m)
│           ├─> closed_by_walls(m)
│           ├─> validate_characters_and_counts(m)
│           └─> check_path(m)
│               ├─> init_pathfinding_data(m, &visited, &queue, &total)
│               └─> run_pathfinding_algorithm(m, &data)
│                   ├─> process_head(m, &data, &ctx, head)  (helper)
│                   │   ├─> process_cell(m, current, &reached_coins, &reached_exit)
│                   │   └─> explore_neighbors(m, current, &ctx)
│                   │       └─> enqueue_neighbor(...) (helper interno)
│                   └─> validate_pathfinding_results(m, reached_coins, reached_exit)

└─> game_start(&m)
    ├─> allocate_game_memory()
    ├─> init_map_data(g, &m)
    ├─> init_mlx(g)  (MLX)
    ├─> create_window(g)  (MLX)
    ├─> texture_loader(g)
    │   └─> mlx_xpm_file_to_image / mlx_* (MLX calls)
    ├─> setup_hooks(g)
    │   ├─> mlx_key_hook(win, on_key_press, g)  (MLX)
    │   ├─> mlx_hook(win, 17, 0, on_window_close, g) (MLX)
    │   └─> mlx_loop_hook(mlx, loop_animation, g) (MLX)
    └─> mlx_loop(mlx)  (MLX event loop)
        ├─> on_key_press(key, g)
        │   └─> try_move(g, dx, dy)
        │       ├─> validar destino (pared?)
        │       ├─> si C: remaining_c-- y grid[ny][nx] = '0'
        │       ├─> si E y remaining_c == 0: terminar juego
        │       └─> actualizar g->px, g->py, g->moves
        ├─> on_window_close(g) -> cleanup y exit
        └─> loop_animation(g)
            ├─> actualizar ticks/frames coin/player
            └─> render(g)
                ├─> render_map(g)
                │   └─> render_tile(g, x, y)
                │       ├─> elegir tile segun grid[y][x]
                │       └─> MLX: mlx_put_image_to_window(mlx, win, tile, x*ts, y*ts)
                └─> render_ui(g) -> mlx_string_put(...) (MLX)

---

## Versión simplificada mínima (arquitectura propuesta)
Si quisieras una versión mínima (por ejemplo para aprender o testear la lógica sin MLX), puedes reducir el proyecto a estas piezas:

Archivos mínimos:
- src/main.c
- src/map_io.c   // leer fichero y devolver char** lines
- src/map.c      // init_map, validate_map, free_map
- src/pathfinding.c // BFS check_path
- src/game_console.c // reemplaza MLX: imprime mapa en consola, procesa teclas con getchar()
- includes/map.h

Funciones mínimas y responsabilidades
1. main(argc, argv)
   - parse args
   - if (!parse_map(path, &m)) exit(1)
   - game_loop_console(&m)

2. parse_map(path, &m)
   - lines = read_lines(path)
   - validate_and_init_map(&m, lines, len)

3. validate_and_init_map(&m, lines, len)
   - init_map_struct
   - if (!is_rectangular || !validate_chars) return 0
   - if (!check_path(&m)) return 0

4. game_loop_console(&m)
   - while (true):
   - print_grid(m)
   - ch = getchar()
   - if ch in WASD: try_move_console(&m, dx, dy)
   - if remaining_c == 0 and position == E -> print "ganaste" y break

Ventajas de la versión simplificada:
- No dependes de MLX (más fácil compilar y depurar).
- Puedes centrarte en lógica de mapas y pathfinding.
- Ideal para aprender C: leer archivos, manejar memoria, punteros y estructuras.

Ejemplo rápido de `try_move_console`:
```c
int try_move_console(t_map *m, int dx, int dy) {
    int nx = m->px + dx;
    int ny = m->py + dy;
    if (nx < 0 || ny < 0 || nx >= m->w || ny >= m->h) return 0;
    if (m->grid[ny][nx] == '1') return 0; // pared
    if (m->grid[ny][nx] == 'C') m->count_c--, m->grid[ny][nx] = '0';
    m->px = nx; m->py = ny;
    return 1;
}
```

---

## Consejos para estudiar el código en C
1. Empieza por `main.c`, sigue la llamada a `parse_map`, y desde ahí avanza a `map_init.c` y `map_validation.c`.
2. Añade `printf` para ver valores intermedios (p. ej. imprimir `w,h,px,py` tras inicializar).
3. Usa `valgrind` o `-fsanitize=address` para detectar fugas y errores de memoria.
4. Practica reescribiendo la versión simplificada (consola) antes de trabajar con MLX.

---

Si quieres, puedo:
- añadir un diagrama en ASCII más compacto del call-graph en el propio archivo;
- crear la versión simplificada (código completo) dentro de una carpeta `minimal/` para que la compiles y la uses como laboratorio didáctico.

Dime si quieres que incluya la versión simplificada con código listo para compilar; la puedo añadir como `minimal/` con un `Makefile` y explicaciones.
