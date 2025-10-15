#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/map.h"

static char *read_line(FILE *f)
{
    char buf[1024];
    if (!fgets(buf, sizeof(buf), f))
        return (NULL);
    size_t len = strlen(buf);
    if (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r'))
        buf[--len] = '\0';
    char *s = malloc(len + 1);
    if (!s) return (NULL);
    memcpy(s, buf, len + 1);
    return s;
}

int parse_map(const char *path, t_map *m)
{
    FILE *f = fopen(path, "r");
    char *lines[1024];
    int len = 0;

    if (!f) return 0;
    while (len < 1024)
    {
        char *ln = read_line(f);
        if (!ln) break;
        lines[len++] = ln;
    }
    fclose(f);
    if (len == 0) return 0;
    return validate_and_init_map(m, lines, len);
}
