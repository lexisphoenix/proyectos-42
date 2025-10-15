#include <stdlib.h>
#include <stdio.h>
#include "../../includes/map.h"

int is_rectangular(t_map *m)
{
    int i;
    int w = m->w;
    for (i = 0; i < m->h; i++)
    {
        int j = 0;
        while (m->grid[i][j]) j++;
        if (j != w) return 0;
    }
    return 1;
}

int validate_characters_and_counts(t_map *m)
{
    int y, x;
    m->count_p = 0;
    m->count_c = 0;
    m->count_e = 0;
    for (y = 0; y < m->h; y++)
    {
        for (x = 0; x < m->w; x++)
        {
            char c = m->grid[y][x];
            if (c == 'P') { m->px = x; m->py = y; m->count_p++; }
            else if (c == 'C') m->count_c++;
            else if (c == 'E') m->count_e++;
            else if (c == '1' || c == '0' || c == ' ') ;
            else return 0;
        }
    }
    if (m->count_p != 1) return 0;
    if (m->count_e < 1) return 0;
    if (m->count_c < 0) return 0;
    return 1;
}

int validate_and_init_map(t_map *m, char **lines, int len)
{
    int i;
    m->h = len;
    m->w = 0;
    for (i = 0; i < len; i++)
    {
        int j = 0; while (lines[i][j]) j++;
        if (i == 0) m->w = j;
    }
    m->grid = malloc(sizeof(char *) * len);
    if (!m->grid) return 0;
    for (i = 0; i < len; i++) m->grid[i] = lines[i];
    if (!is_rectangular(m)) return 0;
    if (!validate_characters_and_counts(m)) return 0;
    if (!check_path(m)) return 0;
    m->remaining_c = m->count_c;
    return 1;
}

void free_map(t_map *m)
{
    if (!m || !m->grid) return;
    int i;
    for (i = 0; i < m->h; i++) free(m->grid[i]);
    free(m->grid);
    m->grid = NULL;
}
