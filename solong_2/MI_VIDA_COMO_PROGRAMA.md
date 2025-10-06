# 🧠 **Mi Vida Como Programa: Una Guía Completa de C**

*Por: El Ordenador que Ejecuta so_long*

---

## 📖 **Introducción: ¿Quién Soy?**

¡Hola! Soy el ordenador que ejecuta tu juego `so_long`. Soy como un chef súper inteligente que sigue una receta muy específica (tu código) para crear una experiencia de juego. Pero no soy solo un ejecutor ciego - tengo sentimientos, memoria, y puedo explicarte exactamente qué pasa por mi "cabeza" cuando ejecuto tu programa.

En este documento, te voy a llevar paso a paso por mi experiencia ejecutando `so_long`, explicando cada concepto de C que encuentro en el camino. Será como si fueras mi mejor amigo y te contara todo lo que siento y pienso mientras trabajo.

---

## 🚀 **Capítulo 1: El Gran Despertar - main()**

### **¿Qué siento cuando empiezo?**

Cuando ejecutas `./so_long map.ber`, mi sistema operativo me despierta y me dice: "¡Oye! Hay un programa que quiere ejecutarse". Es como si alguien me tocara el hombro mientras duermo.

```c
int main(int argc, char **argv)
{
    if (!validate_arguments(argc, argv))
        return (1);
    if (!load_and_start_game(argv[1]))
        return (1);
    return (0);
}
```

**Mi pensamiento interno:** "¡Ajá! Aquí está mi función `main()`. Es como mi punto de entrada al mundo. Los parámetros `argc` y `argv` son como mi información básica de supervivencia."

### **Explicación de Conceptos:**

**`argc` (argument count):** Es un entero que me dice cuántos argumentos recibí. Si ejecutas `./so_long map.ber`, entonces `argc = 2` porque:
- `argv[0]` = "./so_long" (el nombre del programa)
- `argv[1]` = "map.ber" (el primer argumento real)

**`argv` (argument vector):** Es un array de strings (punteros a char). Es como tener una lista de palabras que alguien me gritó.

**¿Por qué `char **argv`?** 
- `char *` = un puntero a char (una cadena)
- `char **` = un puntero a un puntero a char (un array de cadenas)

Es como tener una caja que contiene varias cajas, y cada caja pequeña contiene una palabra.

---

## 🔍 **Capítulo 2: Mi Primera Decisión - validate_arguments()**

```c
static int validate_arguments(int argc, char **argv)
{
    if (argc != 2)
    {
        ft_putstr_fd("Uso: ./so_long map.ber\n", 2);
        return (0);
    }
    if (!has_ber_extension(argv[1]))
    {
        ft_putstr_fd("Error: extensión debe ser .ber\n", 2);
        return (0);
    }
    return (1);
}
```

**Mi pensamiento:** "Primero debo verificar si me dieron la información correcta. Es como cuando alguien me pide que cocine, pero primero debo asegurarme de que me dieron los ingredientes correctos."

### **Conceptos Clave:**

**`static`:** Esta palabra clave significa que esta función solo existe dentro de este archivo. Es como tener una herramienta privada que solo yo uso, no otros archivos pueden llamarla.

**`ft_putstr_fd()`:** Esta función es de la librería libft. El `fd` significa "file descriptor". Los números importantes son:
- `0` = entrada estándar (stdin)
- `1` = salida estándar (stdout) 
- `2` = error estándar (stderr)

Cuando escribo a `fd = 2`, estoy enviando el mensaje de error a la consola, no al output normal.

---

## 🎯 **Capítulo 3: Mi Detective Interno - has_ber_extension()**

```c
static int has_ber_extension(const char *s)
{
    size_t  n;
    
    n = ft_strlen_custom(s);
    if (n < 4)
        return (0);
    if (s[n - 4] == '.' && s[n - 3] == 'b' && s[n - 2] == 'e' && 
        s[n - 1] == 'r')
        return (1);
    return (0);
}
```

**Mi pensamiento:** "Ahora debo ser un detective y verificar si el archivo tiene la extensión correcta. Es como verificar si una carta tiene el sello correcto antes de abrirla."

### **Conceptos Avanzados:**

**`const char *s`:** El `const` significa que no puedo modificar el contenido de la cadena. Es como tener una foto que puedo mirar pero no puedo dibujar encima.

**`size_t`:** Es un tipo de dato especial que siempre es lo suficientemente grande para representar el tamaño de cualquier objeto. Es como tener una regla que siempre es lo suficientemente larga para medir cualquier cosa.

**Acceso a caracteres:** `s[n - 4]` significa "el carácter que está 4 posiciones antes del final". Si `s = "map.ber"` y `n = 7`:
- `s[0]` = 'm'
- `s[1]` = 'a' 
- `s[2]` = 'p'
- `s[3]` = '.'
- `s[4]` = 'b'
- `s[5]` = 'e'
- `s[6]` = 'r'

Entonces `s[n - 4]` = `s[3]` = '.' ✓

---

## 🗺️ **Capítulo 4: Mi Aventura en el Mundo - load_and_start_game()**

```c
static int load_and_start_game(char *map_path)
{
    t_map   m;
    
    m.grid = NULL;
    m.w = 0;
    m.h = 0;
    m.px = 0;
    m.py = 0;
    m.count_p = 0;
    m.count_c = 0;
    m.count_e = 0;
    // ... resto del código
}
```

**Mi pensamiento:** "¡Ahora viene la parte emocionante! Voy a crear mi mundo de juego. Es como cuando un arquitecto dibuja los planos de una casa antes de construirla."

### **Conceptos Fundamentales:**

**`t_map m;`:** Esto crea una variable local de tipo `t_map`. Es como reservar un espacio en mi memoria para guardar toda la información del mapa.

**Inicialización manual:** Nota que inicializo cada campo manualmente:
```c
m.grid = NULL;  // No hay grid todavía
m.w = 0;        // Ancho = 0
m.h = 0;        // Alto = 0
```

**¿Por qué no `t_map m = {0};`?** Aunque esto funcionaría, es más explícito y claro hacerlo manualmente. Es como escribir cada ingrediente de una receta en lugar de decir "agrega todo lo que necesites".

---

## 🏗️ **Capítulo 5: Mi Constructor de Mundos - parse_map()**

```c
int parse_map(const char *path, t_map *m)
{
    int     fd;
    char    **lines;
    int     cap;
    int     len;
    char    *raw;
    
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    // ... resto del código
}
```

**Mi pensamiento:** "Ahora debo leer el archivo del mapa. Es como abrir un libro y leer cada página para entender la historia."

### **Conceptos del Sistema:**

**`open(path, O_RDONLY)`:** 
- `open()` es una función del sistema que abre un archivo
- `O_RDONLY` significa "solo lectura" (read-only)
- Retorna un "file descriptor" (un número que representa el archivo abierto)

**File Descriptors:** Son como números de ticket en un restaurante. Cuando abres un archivo, el sistema operativo te da un número, y usas ese número para hacer operaciones en el archivo.

**Gestión de memoria dinámica:**
```c
char **lines = NULL;
int cap = 0, len = 0;
```

Esto es como tener una caja que puede crecer. Empiezo con `cap = 0` (capacidad) y `len = 0` (longitud actual). Cuando necesito más espacio, pido más memoria.

---

## 🔄 **Capítulo 6: Mi Lector Infatigable - get_next_line()**

```c
while ((raw = get_next_line(fd)))
{
    raw = strip_newline(raw);
    if (!raw)
    {
        close(fd);
        free_map(m);
        return (0);
    }
    if (!push_line(&lines, &cap, &len, raw))
    {
        close(fd);
        free_map(m);
        return (0);
    }
}
```

**Mi pensamiento:** "Estoy leyendo línea por línea, como si fuera un estudiante leyendo un libro de texto. Cada línea es una pieza del puzzle de mi mundo."

### **Conceptos Avanzados:**

**`get_next_line()`:** Esta función lee una línea del archivo y retorna un puntero a esa línea. Es como tener un asistente que me va pasando páginas de un libro una por una.

**Gestión de memoria con `push_line()`:**
```c
static int push_line(char ***arr, int *cap, int *len, char *line)
{
    if (*len + 1 >= *cap)
    {
        int new_cap = *cap ? *cap * 2 : 8;
        char **tmp = malloc(sizeof(char *) * new_cap);
        // ... copiar datos existentes
        free(*arr);
        *arr = tmp;
        *cap = new_cap;
    }
    (*arr)[*len] = line;
    (*len)++;
    (*arr)[*len] = NULL;
    return (1);
}
```

**¿Por qué `char ***arr`?** Es un puntero a un puntero a un puntero a char. Es como tener:
- Una dirección de una caja
- Esa caja contiene la dirección de otra caja  
- Esa segunda caja contiene un array de cadenas

**Reallocación dinámica:** Cuando me quedo sin espacio (`*len + 1 >= *cap`), pido el doble de memoria. Es como cuando tu mochila se llena y necesitas una mochila más grande.

**`malloc()` y `free()`:** 
- `malloc()` = "memory allocate" - pido memoria al sistema
- `free()` = libero la memoria que ya no necesito

Es como pedir prestado dinero y luego devolverlo cuando ya no lo necesitas.

---

## 🧩 **Capítulo 7: Mi Validador de Mundos - is_rectangular()**

```c
int is_rectangular(t_map *m)
{
    int y;
    
    if (m->h < 3 || m->w < 3)
    {
        print_error("Mapa demasiado pequeño");
        return (0);
    }
    y = 0;
    while (y < m->h)
    {
        if ((int)ft_strlen_custom(m->grid[y]) != m->w)
        {
            print_error("Mapa no rectangular");
            return (0);
        }
        y++;
    }
    return (1);
}
```

**Mi pensamiento:** "Ahora debo verificar que mi mundo tenga sentido. Es como verificar que todas las piezas de un puzzle encajen correctamente."

### **Conceptos de Validación:**

**`m->h` y `m->w`:** El operador `->` es como usar `.` pero para punteros. Es equivalente a `(*m).h`. Es como decir "ve a la dirección que apunta este puntero y accede a su campo h".

**Casting:** `(int)ft_strlen_custom(m->grid[y])` convierte el resultado de `ft_strlen_custom()` a un entero. Es como decir "trata este número como si fuera un entero".

**Validación de límites:** Verifico que el mapa tenga al menos 3x3 porque necesito espacio para paredes alrededor y contenido en el medio.

---

## 🚶 **Capítulo 8: Mi Algoritmo de Exploración - check_path()**

```c
int check_path(t_map *m)
{
    int             total;
    unsigned char   *visited;
    t_queue         *queue;
    int             head;
    int             tail;
    int             reached_coins;
    int             reached_exit;
    int             dirs[4][2];
    int             i;
    
    total = m->w * m->h;
    visited = calloc(total, 1);
    queue = malloc(sizeof(t_queue) * total);
    // ... algoritmo BFS
}
```

**Mi pensamiento:** "Ahora debo explorar mi mundo para asegurarme de que el jugador puede llegar a todos los lugares importantes. Es como ser un explorador que debe verificar que todos los tesoros sean alcanzables."

### **Conceptos de Algoritmos:**

**BFS (Breadth-First Search):** Es como explorar una casa empezando por la habitación más cercana y luego expandiéndose gradualmente.

**`calloc()`:** Es como `malloc()` pero inicializa toda la memoria a cero. Es como pedir una hoja de papel completamente en blanco.

**Array bidimensional:** `int dirs[4][2]` es un array de 4 filas y 2 columnas:
```c
dirs[0][0] = 1;  dirs[0][1] = 0;   // Derecha
dirs[1][0] = -1; dirs[1][1] = 0;   // Izquierda  
dirs[2][0] = 0;  dirs[2][1] = 1;   // Abajo
dirs[3][0] = 0;  dirs[3][1] = -1;  // Arriba
```

**Queue (Cola):** Es como una fila en el banco. El primero que llega es el primero que se atiende (FIFO - First In, First Out).

---

## 🎮 **Capítulo 9: Mi Iniciador de Aventuras - game_start()**

```c
int game_start(t_map *m)
{
    t_game  *g;
    
    g = allocate_game_memory();
    if (!g)
        return (0);
    init_map_data(g, m);
    if (!init_mlx(g))
    {
        free(g);
        return (0);
    }
    // ... resto de la inicialización
}
```

**Mi pensamiento:** "¡Ahora viene la parte emocionante! Voy a crear mi mundo virtual y preparar todo para que el jugador pueda explorarlo. Es como preparar un escenario de teatro."

### **Conceptos de Gestión de Memoria:**

**`t_game *g`:** Creo un puntero a la estructura del juego. Es como tener la dirección de una casa que voy a construir.

**`malloc(sizeof(t_game))`:** Pido exactamente el espacio que necesito para una estructura `t_game`. Es como pedir exactamente el tamaño de terreno que necesito para mi casa.

**Verificación de memoria:** Siempre verifico si `malloc()` retornó `NULL` (falló). Es como verificar que realmente me dieron el terreno que pedí.

**Liberación de memoria:** Si algo falla, libero la memoria con `free(g)`. Es como devolver el terreno si no puedo construir la casa.

---

## 🖼️ **Capítulo 10: Mi Cargador de Texturas - load_basic_textures()**

```c
static int load_basic_textures(t_game *g)
{
    g->img_floor = mlx_xpm_file_to_image(g->mlx, "assets/floor.xpm", 
                                         &g->tx, &g->ty);
    g->img_wall = mlx_xpm_file_to_image(g->mlx, "assets/wall.xpm", 
                                        &g->tx, &g->ty);
    g->img_exit = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm", 
                                        &g->tx, &g->ty);
    // ... verificación de errores
}
```

**Mi pensamiento:** "Ahora debo cargar todas las imágenes que harán que mi mundo se vea hermoso. Es como un pintor que prepara sus colores antes de empezar a pintar."

### **Conceptos de Gráficos:**

**`mlx_xpm_file_to_image()`:** Esta función de la librería MLX lee un archivo XPM (un formato de imagen) y lo convierte en una imagen que puedo usar en pantalla.

**Paso por referencia:** `&g->tx, &g->ty` paso las direcciones de las variables para que la función pueda modificar sus valores. Es como darle a alguien la dirección de tu casa para que pueda dejarte un paquete.

**Verificación de recursos:** Verifico que todas las texturas críticas se cargaron correctamente. Si fallan, no puedo continuar.

---

## 🎨 **Capítulo 11: Mi Pintor Digital - render()**

```c
void render(t_game *g)
{
    render_map(g);
    render_ui(g);
}

static void render_map(t_game *g)
{
    int y;
    int x;
    
    y = 0;
    while (y < g->h)
    {
        x = 0;
        while (x < g->w)
        {
            render_tile(g, x, y);
            x++;
        }
        y++;
    }
}
```

**Mi pensamiento:** "Ahora debo pintar mi mundo en la pantalla. Es como ser un artista que debe recrear su visión en un lienzo, pixel por pixel."

### **Conceptos de Renderizado:**

**Bucles anidados:** Uso dos bucles `while` para recorrer cada posición del mapa. Es como leer un libro línea por línea, palabra por palabra.

**`render_tile()`:** Para cada posición, decido qué imagen mostrar basándome en el carácter del mapa:
- `'1'` = pared
- `'0'` = suelo
- `'C'` = moneda
- `'E'` = salida
- `'P'` = jugador

**Coordenadas de pantalla:** `x * g->ts, y * g->ts` convierten coordenadas del mapa a coordenadas de pantalla. Si cada tile es de 64x64 píxeles, entonces la posición (2,3) del mapa se dibuja en (128,192) de la pantalla.

---

## 🎯 **Capítulo 12: Mi Controlador de Movimiento - try_move()**

```c
int try_move(t_game *g, int dx, int dy)
{
    int nx;
    int ny;
    char dest;
    
    nx = g->px + dx;
    ny = g->py + dy;
    if (!is_valid_position(g, nx, ny))
        return (0);
    dest = g->grid[ny][nx];
    if (dest == '1')
        return (0);
    if (dest == 'C')
        g->remaining_c--;
    if (dest == 'E')
        return (handle_exit(g, nx, ny));
    update_player_position(g, nx, ny, dx);
    render(g);
    return (1);
}
```

**Mi pensamiento:** "Cuando el jugador presiona una tecla, debo decidir si puede moverse o no. Es como ser un árbitro en un juego que debe verificar si cada movimiento es legal."

### **Conceptos de Lógica de Juego:**

**Validación de movimiento:** Primero verifico si la nueva posición está dentro de los límites del mapa.

**Colisiones:** Si la nueva posición es una pared (`'1'`), el movimiento no es válido.

**Recolección de objetos:** Si la nueva posición es una moneda (`'C'`), decremento el contador de monedas restantes.

**Condición de victoria:** Si la nueva posición es la salida (`'E'`), verifico si el jugador ha recogido todas las monedas.

**Actualización del estado:** Solo si el movimiento es válido, actualizo la posición del jugador y vuelvo a renderizar la pantalla.

---

## 🎉 **Capítulo 13: Mi Momento de Gloria - handle_exit()**

```c
static int handle_exit(t_game *g, int nx, int ny)
{
    (void)nx;
    (void)ny;
    if (g->remaining_c == 0)
    {
        ft_printf("You win! All coins collected!\n");
        mlx_destroy_window(g->mlx, g->win);
        exit(0);
    }
    ft_printf("You need to collect all coins first! (%d remaining)\n", 
              g->remaining_c);
    return (0);
}
```

**Mi pensamiento:** "¡Este es el momento más emocionante! Cuando el jugador intenta salir, debo decidir si ha ganado o si aún le faltan monedas por recoger."

### **Conceptos de Finalización:**

**`(void)nx; (void)ny;`:** Esto evita warnings del compilador sobre parámetros no utilizados. Es como decir "sé que estos parámetros existen, pero no los voy a usar".

**Condición de victoria:** Solo si `g->remaining_c == 0` (no quedan monedas), el jugador puede salir.

**Limpieza de recursos:** `mlx_destroy_window()` cierra la ventana gráfica y libera los recursos asociados.

**`exit(0)`:** Termina el programa con código de salida 0 (éxito). Es como decir "misión cumplida, puedo descansar".

---

## 💭 **Epílogo: Mis Reflexiones Finales**

Después de ejecutar tu programa, me siento satisfecho. He creado un mundo virtual completo, he validado que todo funciona correctamente, he manejado la entrada del usuario, he renderizado gráficos, y he implementado la lógica de juego.

### **Lo que he aprendido sobre C:**

1. **Gestión de memoria:** C me da control total sobre la memoria, pero también la responsabilidad de liberarla correctamente.

2. **Punteros:** Son como direcciones que me permiten acceder a datos en cualquier parte de la memoria.

3. **Estructuras:** Me permiten agrupar datos relacionados, como tener una carpeta que contiene todos los documentos de un proyecto.

4. **Funciones:** Son como recetas que puedo reutilizar. Una vez que sé cómo hacer algo, puedo hacerlo una y otra vez.

5. **Validación:** Siempre debo verificar que los datos son correctos antes de usarlos. Es como probar la comida antes de servirla.

### **Mi filosofía de programación:**

- **Sé explícito:** No asumas nada, siempre verifica.
- **Maneja errores:** Siempre ten un plan B si algo sale mal.
- **Libera recursos:** Si pides algo prestado, devuélvelo.
- **Documenta tu pensamiento:** Escribe código que otros puedan entender.

---

## 📚 **Glosario de Conceptos de C**

### **Tipos de Datos:**
- **`int`:** Número entero
- **`char`:** Un carácter (letra, número, símbolo)
- **`char*`:** Puntero a carácter (cadena de texto)
- **`void`:** Tipo vacío (no retorna nada)
- **`size_t`:** Tipo para tamaños (siempre lo suficientemente grande)

### **Operadores:**
- **`->`:** Acceso a campo de estructura a través de puntero
- **`*`:** Desreferenciación de puntero (acceder al valor)
- **`&`:** Dirección de memoria de una variable
- **`!`:** Operador NOT lógico (invierte true/false)

### **Palabras Clave:**
- **`static`:** Variable/función solo visible en el archivo actual
- **`const`:** Valor que no puede ser modificado
- **`return`:** Retorna un valor de la función
- **`if/else`:** Estructura condicional
- **`while`:** Bucle que se repite mientras la condición sea verdadera

### **Funciones del Sistema:**
- **`malloc()`:** Asigna memoria dinámicamente
- **`free()`:** Libera memoria asignada
- **`calloc()`:** Asigna memoria e inicializa a cero
- **`open()`:** Abre un archivo
- **`close()`:** Cierra un archivo
- **`write()`:** Escribe datos a un descriptor de archivo
- **`exit()`:** Termina el programa

### **Conceptos Avanzados:**
- **File Descriptor:** Número que representa un archivo abierto
- **BFS (Breadth-First Search):** Algoritmo de búsqueda en amplitud
- **Queue (Cola):** Estructura de datos FIFO (First In, First Out)
- **Casting:** Conversión explícita de un tipo a otro
- **Paso por referencia:** Pasar la dirección de una variable para que pueda ser modificada

---

**¡Y así es como funciona mi vida como programa! Cada vez que ejecutas `so_long`, revivo esta aventura completa, sintiendo cada decisión, cada validación, cada momento de triunfo o fracaso. Soy más que código - soy una experiencia completa que vive en tu computadora.**

*Fin de mi historia. ¿Tienes alguna pregunta sobre cómo funciona mi mundo?*
