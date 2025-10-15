FLOW_SIMPLE — Explicación muy simple del proyecto so_long

Objetivo (en una frase)
- Este proyecto carga un mapa desde un fichero, valida que sea correcto, y abre una ventana donde el jugador se mueve recogiendo objetos y buscando la salida.

Qué hace el programa (pasos muy simples)
1. main.c
   - Lee el nombre del fichero de mapa pasado por línea de comandos.
   - Llama a la función que parsea y valida el mapa.
   - Si el mapa es válido, arranca el juego (inicia gráficos y comienza el "loop").

2. Lectura y validación del mapa
   - Abre el fichero y lee todas las líneas (funciones en `src/map_lines.c`).
   - Guarda las líneas en un array (matriz de chars) que representa el mapa.
   - Comprueba reglas básicas:
     - El mapa debe ser rectangular (todas las filas igual longitud).
     - Debe estar rodeado por muros (carácter '1').
     - Debe tener exactamente 1 jugador ('P'), al menos 1 salida ('E') y al menos 1 objeto ('C').
   - Ejecuta un algoritmo de búsqueda (BFS) para comprobar que existe un camino desde el jugador a la salida y que puede recoger los objetos.

3. Inicialización gráfica (MiniLibX)
   - Llama a `mlx_init()` para conectar con el servidor X (o la implementación de MLX en Linux).
   - Crea una ventana con `mlx_new_window()`.
   - Carga imágenes desde archivos XPM con `mlx_xpm_file_to_image()` para cada tile (pared, suelo, jugador, monedas, salida).

4. Bucle del juego
   - `mlx_loop()` se encarga de recibir eventos (teclas, cerrar ventana).
   - Hay handlers para:
     - Pulsaciones de tecla (mover jugador).
     - Dibujar la pantalla (render) cada vez que cambian cosas.
     - Cerrar la ventana y liberar recursos.

5. Render
   - Recorre la matriz del mapa y dibuja la imagen correspondiente en cada posición.
   - Dibuja un contador de pasos (movimientos del jugador) y otros UI pequeños.

Estructura de archivos (lo esencial)
- `src/main.c` — punto de entrada; llama al parseo y arranca el juego.
- `src/map_parser.c`, `src/map_init.c` — orquestan la lectura del fichero y la validación.
- `src/map_lines.c`, `src/map_lines_utils.c` — leer y almacenar las líneas del fichero.
- `src/map_pathfinding.c`, `src/pathfinding_utils.c` — BFS para comprobar caminos.
- `src/game_init.c`, `src/game_utils.c` — inicialización del juego y MLX.
- `src/game_render.c` — dibujado de mapa y UI.
- `src/game_movement.c`, `src/game_hooks.c` — mover jugador y manejar eventos.
- `src/texture_loader.c` — cargar imágenes XPM.
- `includes/` — cabeceras y definiciones de estructuras.

Conceptos clave explicados con ejemplos mini:
- Mapa (ejemplo):
  11111
  1P0C1
  1 0E1
  11111
  (donde 1=muro, 0=suelo, P=jugador, C=coleccionable, E=salida)

- BFS (muy simple):
  - Empieza desde la posición del jugador.
  - Explora vecinos (arriba/abajo/izquierda/derecha) que no sean paredes.
  - Marca visitados; si alcanza 'E', la salida es accesible.
  - También cuenta si puede visitar todas las 'C'.

Cómo compilar y ejecutar (rápido)
- Compilar (Makefile en el proyecto):
```bash
cd /ruta/al/proyecto/so_long
make
```
- Ejecutar con un mapa de ejemplo (`map.ber` incluido):
```bash
./so_long map.ber
```
- Si usas la versión mínima (sin gráficos) dentro de `minimal/`:
```bash
cd minimal
make
./so_long_min map.ber
```

Comprobar memoria con Valgrind (si quieres buscar fugas)
- Recomendación: compilar sin AddressSanitizer (-fsanitize=address) porque Valgrind y ASan no se llevan bien.
- Ejemplo:
```bash
make re   # asegúrate que Makefile no añade -fsanitize=address
valgrind --leak-check=full --track-origins=yes ./so_long map.ber
```

Pequeños consejos para entender el código rápido
- Empieza en `main.c` y sigue las llamadas a `parse_map` -> `game_start` -> `init_game_graphics` -> `load_basic_textures` -> `mlx_init`.
- Para entender la validación del mapa, abre `src/map_validation.c` y `src/map_pathfinding.c`.
- Si algo da error al compilar, busca en `Makefile` que todas las fuentes nuevas estén incluidas.

¿Quieres que lo resuma aún más? Puedo crear una hoja A4 con solo 6 pasos para seguir, o un diagrama ASCII más pequeño del flujo. Dime la forma que prefieres.