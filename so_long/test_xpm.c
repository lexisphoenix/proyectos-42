#include "mlx.h"
#include <stdio.h>

int main() {
    void *mlx = mlx_init();
    int w,h;
    void *img = mlx_xpm_file_to_image(mlx, "assets/coin.xpm", &w, &h);
    printf("img=%p size=%dx%d\n", img, w, h);
    return 0;
}