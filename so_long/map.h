#ifndef MAP_H
# define MAP_H

typedef struct s_map {
    char **grid;
    int   w;
    int   h;
    int   px; // se usará más adelante
    int   py; // se usará más adelante
    int   count_p, count_c, count_e; // se usarán más adelante
} t_map;

int  parse_map(const char *path, t_map *m);
void free_map(t_map *m);

#endif
