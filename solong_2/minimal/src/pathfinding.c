#include <stdlib.h>
#include "../../includes/map.h"

int check_path(t_map *m)
{
    int w = m->w;
    int h = m->h;
    unsigned char *visited = malloc(w * h);
    t_queue *queue = malloc(sizeof(t_queue) * w * h);
    int head = 0, tail = 0;
    int reached_c = 0, reached_e = 0;

    if (!visited || !queue) return 0;
    for (int i = 0; i < w*h; i++) visited[i] = 0;
    queue[tail].x = m->px; queue[tail].y = m->py; tail++;
    visited[m->py * w + m->px] = 1;
    while (head < tail)
    {
        t_queue cur = queue[head++];
        char c = m->grid[cur.y][cur.x];
        if (c == 'C') reached_c++;
        if (c == 'E') reached_e = 1;
        int dx[4] = {1,-1,0,0};
        int dy[4] = {0,0,1,-1};
        for (int k = 0; k < 4; k++)
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            if (visited[ny*w + nx]) continue;
            char cc = m->grid[ny][nx];
            if (cc == '1') continue;
            visited[ny*w + nx] = 1;
            queue[tail].x = nx; queue[tail].y = ny; tail++;
        }
    }
    int ok = (reached_c == m->count_c) && reached_e;
    free(visited); free(queue);
    return ok;
}
