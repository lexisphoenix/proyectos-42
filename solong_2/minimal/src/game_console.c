#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../includes/map.h"

int try_move_console(t_map *m, int dx, int dy)
{
    int nx = m->px + dx;
    int ny = m->py + dy;
    if (nx < 0 || ny < 0 || nx >= m->w || ny >= m->h) return 0;
    char c = m->grid[ny][nx];
    if (c == '1') return 0;
    if (c == 'C') { m->remaining_c--; m->grid[ny][nx] = '0'; }
    m->px = nx; m->py = ny;
    return 1;
}

void print_grid(t_map *m)
{
    for (int y = 0; y < m->h; y++)
        printf("%s\n", m->grid[y]);
}

int game_loop_console(t_map *m)
{
    char c;
    while (1)
    {
        print_grid(m);
        if (m->remaining_c == 0 && m->grid[m->py][m->px] == 'E')
        {
            printf("Has ganado!\n");
            break;
        }
        printf("WASD to move, q to quit\n");
        c = getchar();
        if (c == 'q') break;
        if (c == 'w') try_move_console(m, 0, -1);
        if (c == 's') try_move_console(m, 0, 1);
        if (c == 'a') try_move_console(m, -1, 0);
        if (c == 'd') try_move_console(m, 1, 0);
        // consume newline
        while (c != '\n' && (c = getchar()) != '\n' && c != EOF) ;
    }
    free_map(m);
    return 0;
}
