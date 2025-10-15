#include <stdio.h>
#include <stdlib.h>
#include "../../includes/map.h"

int parse_map(const char *path, t_map *m);
int game_loop_console(t_map *m);

int main(int argc, char **argv)
{
    t_map m;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s map.ber\n", argv[0]);
        return (1);
    }
    if (!parse_map(argv[1], &m))
    {
        fprintf(stderr, "Failed to parse map\n");
        return (1);
    }
    game_loop_console(&m);
    return (0);
}
