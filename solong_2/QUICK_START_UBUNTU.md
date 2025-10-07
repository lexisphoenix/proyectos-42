# 🚀 **Instrucciones Rápidas para Ubuntu**

## **Opción 1: Instalación Automática (Recomendada)**
```bash
# Ejecutar el script de instalación automática
./install_ubuntu.sh
```

## **Opción 2: Instalación Manual**
```bash
# 1. Instalar dependencias
sudo apt update
sudo apt install -y build-essential git libx11-dev libxext-dev libxrandr-dev libxss-dev libxcursor-dev libxinerama-dev libxi-dev libgl1-mesa-dev

# 2. Compilar minilibx
cd minilibx && make && cd ..

# 3. Compilar el proyecto
make

# 4. Ejecutar el juego
./so_long map.ber
```

## **Comandos Útiles**
```bash
# Verificar dependencias
make -f Makefile.ubuntu check_deps

# Instalar dependencias automáticamente
make -f Makefile.ubuntu install-deps

# Compilar con verificaciones
make -f Makefile.ubuntu ubuntu-build

# Limpiar todo
make -f Makefile.ubuntu ubuntu-clean

# Recompilar desde cero
make -f Makefile.ubuntu ubuntu-rebuild

# Ver información del sistema
make -f Makefile.ubuntu info
```

## **Solución de Problemas**
```bash
# Si hay errores de formato de archivo
find . -name "*.o" -delete
make fclean && make

# Si minilibx no compila
sudo apt install -y libx11-dev libxext-dev
cd minilibx && make

# Si el ejecutable no funciona
chmod +x so_long
```

## **Verificación Final**
```bash
# Verificar que todo está listo
ls -la so_long          # Debe existir el ejecutable
ls -la minilibx/libmlx.a # Debe existir la librería
./so_long map.ber       # Debe abrir el juego
```

¡Listo para Ubuntu! 🐧


