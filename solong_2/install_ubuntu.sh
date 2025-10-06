#!/bin/bash

# 🐧 Script de Instalación Automática para Ubuntu
# so_long - Instalación de Dependencias y Compilación

echo "🐧 Instalando so_long para Ubuntu..."
echo "=================================="

# Colores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Función para mostrar mensajes
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Verificar si estamos en Ubuntu
if ! command -v apt &> /dev/null; then
    print_error "Este script está diseñado para Ubuntu/Debian. No se detectó apt."
    exit 1
fi

print_status "Detectado sistema Ubuntu/Debian"

# Actualizar sistema
print_status "Actualizando sistema..."
sudo apt update

# Instalar herramientas de compilación
print_status "Instalando herramientas de compilación..."
sudo apt install -y build-essential git

# Instalar dependencias de X11
print_status "Instalando dependencias de X11..."
sudo apt install -y libx11-dev libxext-dev libxrandr-dev libxss-dev libxcursor-dev libxinerama-dev libxi-dev libgl1-mesa-dev

print_success "Dependencias instaladas correctamente"

# Verificar que minilibx existe
if [ ! -d "minilibx" ]; then
    print_error "Directorio minilibx no encontrado"
    print_status "Descargando minilibx para Linux..."
    git clone https://github.com/42Paris/minilibx-linux.git minilibx
fi

# Compilar minilibx
print_status "Compilando minilibx..."
cd minilibx
if make; then
    print_success "minilibx compilado correctamente"
else
    print_error "Error al compilar minilibx"
    print_warning "Verifica que las dependencias de X11 están instaladas"
    exit 1
fi

# Volver al directorio principal
cd ..

# Limpiar archivos objeto previos
print_status "Limpiando archivos objeto previos..."
find . -name "*.o" -delete 2>/dev/null || true

# Compilar el proyecto
print_status "Compilando so_long..."
if make; then
    print_success "so_long compilado correctamente"
else
    print_error "Error al compilar so_long"
    print_warning "Ejecuta 'make fclean && make' para una compilación limpia"
    exit 1
fi

# Verificar que el ejecutable existe
if [ -f "so_long" ]; then
    print_success "Ejecutable so_long creado"
    chmod +x so_long
else
    print_error "No se pudo crear el ejecutable so_long"
    exit 1
fi

# Verificar que el mapa existe
if [ -f "map.ber" ]; then
    print_success "Mapa de ejemplo encontrado"
else
    print_warning "No se encontró map.ber"
fi

echo ""
echo "🎉 ¡Instalación completada!"
echo "=========================="
echo ""
echo "Para ejecutar el juego:"
echo "  ./so_long map.ber"
echo ""
echo "Para limpiar y recompilar:"
echo "  make fclean && make"
echo ""
echo "¡Disfruta jugando so_long! 🎮"