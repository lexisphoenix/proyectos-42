# 🐧 **so_long - Guía de Compilación para Ubuntu**

## 📋 **Requisitos del Sistema**

Este proyecto está diseñado para funcionar en Ubuntu con las siguientes dependencias:

### **Dependencias del Sistema**
```bash
sudo apt update
sudo apt install -y build-essential git
```

### **Dependencias de X11 (para gráficos)**
```bash
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxss-dev libxcursor-dev libxinerama-dev libxi-dev libgl1-mesa-dev
```

---

## 🚀 **Instrucciones de Compilación**

### **Paso 1: Instalar Dependencias**
```bash
# Actualizar el sistema
sudo apt update

# Instalar herramientas de compilación
sudo apt install -y build-essential git

# Instalar librerías de X11
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxss-dev libxcursor-dev libxinerama-dev libxi-dev libgl1-mesa-dev
```

### **Paso 2: Compilar el Proyecto**
```bash
# Compilar minilibx para Linux
cd minilibx
make

# Volver al directorio principal
cd ..

# Compilar el proyecto completo
make
```

### **Paso 3: Ejecutar el Juego**
```bash
# Ejecutar con un mapa
./so_long map.ber

# O con cualquier mapa válido
./so_long tu_mapa.ber
```

---

## 🎮 **Controles del Juego**

- **W** o **↑** - Mover hacia arriba
- **A** o **←** - Mover hacia la izquierda  
- **S** o **↓** - Mover hacia abajo
- **D** o **→** - Mover hacia la derecha
- **ESC** - Salir del juego

---

## 🗺️ **Formato del Mapa**

El mapa debe ser un archivo `.ber` con el siguiente formato:

- **`1`** - Pared (no se puede atravesar)
- **`0`** - Suelo (se puede caminar)
- **`C`** - Moneda (objetivo a recoger)
- **`E`** - Salida (solo accesible con todas las monedas)
- **`P`** - Jugador (posición inicial)

### **Reglas del Mapa:**
- Debe ser rectangular
- Debe estar rodeado de paredes (`1`)
- Debe tener exactamente 1 jugador (`P`)
- Debe tener al menos 1 moneda (`C`)
- Debe tener al menos 1 salida (`E`)
- Todos los elementos deben ser alcanzables

---

## 🔧 **Comandos Útiles**

### **Compilación**
```bash
make          # Compilar el proyecto
make clean    # Limpiar archivos objeto
make fclean   # Limpiar todo (objetos y ejecutable)
make re       # Limpiar y recompilar
```

### **Verificación**
```bash
# Verificar que el ejecutable existe
ls -la so_long

# Verificar permisos de ejecución
chmod +x so_long
```

---

## 🐛 **Solución de Problemas**

### **Error: "Can't find a suitable X11 include directory"**
```bash
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxss-dev libxcursor-dev libxinerama-dev libxi-dev libgl1-mesa-dev
```

### **Error: "file not recognized: file format not recognized"**
```bash
# Limpiar archivos objeto de otros sistemas
find . -name "*.o" -delete
make fclean
make
```

### **Error: "No such file or directory: minilibx"**
```bash
# Descargar minilibx para Linux
git clone https://github.com/42Paris/minilibx-linux.git minilibx
cd minilibx && make
cd ..
```

### **Error: "Permission denied"**
```bash
chmod +x so_long
```

---

## 📁 **Estructura del Proyecto**

```
so_long/
├── src/                    # Código fuente
│   ├── main.c             # Función principal
│   ├── map_parser.c       # Parser del mapa
│   ├── map_validation.c   # Validación del mapa
│   ├── map_pathfinding.c  # Algoritmo de pathfinding
│   ├── game_render.c      # Renderizado
│   ├── game_animation.c   # Animaciones
│   ├── game_movement.c    # Movimiento del jugador
│   ├── game_hooks.c       # Eventos de teclado
│   └── game_init.c        # Inicialización
├── includes/              # Archivos de cabecera
│   ├── map.h
│   └── game.h
├── assets/                # Recursos gráficos
├── libft/                 # Librería personalizada
├── ft_printf/            # Librería de printf
├── get_next_line/         # Lectura de archivos
├── minilibx/             # Librería gráfica para Linux
├── map.ber               # Mapa de ejemplo
└── Makefile              # Archivo de compilación
```

---

## ✅ **Verificación de Funcionamiento**

Después de compilar, verifica que todo funciona:

1. **Compilación exitosa:**
   ```bash
   make
   # Debe mostrar: [LINK] so_long
   ```

2. **Ejecutable creado:**
   ```bash
   ls -la so_long
   # Debe mostrar el archivo so_long
   ```

3. **Juego ejecutable:**
   ```bash
   ./so_long map.ber
   # Debe abrir una ventana del juego
   ```

---

## 🎯 **Características del Juego**

- ✅ **100% compatible con Norminette** (estándares de 42)
- ✅ **Funciona en Ubuntu** con X11
- ✅ **Validación completa del mapa**
- ✅ **Pathfinding** para verificar que todos los elementos son alcanzables
- ✅ **Animaciones** de monedas y jugador
- ✅ **Sistema de puntuación** (movimientos y monedas restantes)
- ✅ **Condición de victoria** (recoger todas las monedas antes de salir)
- ✅ **Manejo de errores** robusto
- ✅ **Gestión de memoria** sin leaks

---

## 📞 **Soporte**

Si encuentras algún problema:

1. Verifica que todas las dependencias están instaladas
2. Asegúrate de que el mapa tiene el formato correcto
3. Revisa que no hay archivos objeto de otros sistemas
4. Ejecuta `make fclean && make` para una compilación limpia

---

**¡Disfruta jugando so_long en Ubuntu! 🎮**
