/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anieto-m <anieto-m@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 15:22:24 by anieto-m          #+#    #+#             */
/*   Updated: 2025/09/18 13:11:34 by anieto-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

char *get_next_line(int fd);

// helpers
static size_t	slen(const char *s){ size_t i=0; while(s && s[i]) i++; return i; }
static char	*strip_nl(char *s){
	if (!s) return NULL;
	size_t n = slen(s);
	while (n && (s[n-1]=='\n' || s[n-1]=='\r' || s[n-1]==' ' || s[n-1]=='\t'))
		s[--n] = '\0';
	if (n == 0) { free(s); return NULL; }
	return s;
}

static void	err(const char *m){
	write(2,"Error\n",6);
	write(2,m,slen(m));
	write(2,"\n",1);
}

// --- validaciones ---
static int	is_rectangular(t_map *m){
	if (m->h < 3 || m->w < 3){ err("Mapa demasiado pequeño"); return 0; }
	for (int y=0; y<m->h; y++){
		if ((int)slen(m->grid[y]) != m->w){ err("Mapa no rectangular"); return 0; }
	}
	return 1;
}

static int	closed_by_walls(t_map *m){
	for (int x=0; x<m->w; x++){
		if (m->grid[0][x] != '1' || m->grid[m->h-1][x] != '1'){
			err("Bordes sup/inf sin muro"); return 0;
		}
	}
	for (int y=0; y<m->h; y++){
		if (m->grid[y][0] != '1' || m->grid[y][m->w-1] != '1'){
			err("Bordes laterales sin muro"); return 0;
		}
	}
	return 1;
}

static int	chars_and_counts(t_map *m){
	int cP=0, cC=0, cE=0;
	for (int y=0; y<m->h; y++){
		for (int x=0; x<m->w; x++){
			char c = m->grid[y][x];
			if (c!='0' && c!='1' && c!='C' && c!='E' && c!='P'){
				err("Carácter inválido"); return 0;
			}
			if (c=='P'){ cP++; m->px=x; m->py=y; }
			else if (c=='C') cC++;
			else if (c=='E') cE++;
		}
	}
	if (cP!=1){ err("Debe haber exactamente 1 P"); return 0; }
	if (cC<1){  err("Debe haber al menos 1 C"); return 0; }
	if (cE<1){  err("Debe haber al menos 1 E"); return 0; }
	m->count_p=cP; m->count_c=cC; m->count_e=cE;
	return 1;
}

// BFS
typedef struct s_q { int x,y; } t_q;
static int	in_bounds(t_map *m, int x, int y){
	return (x>=0 && x<m->w && y>=0 && y<m->h);
}

static int check_path(t_map *m){
	int total = m->w * m->h;
	unsigned char *vis = calloc(total, 1);
	t_q *q = malloc(sizeof(t_q)*total);
	if (!vis || !q){ free(vis); free(q); err("Memoria (path)"); return 0; }

	int head=0, tail=0, rc=0, re=0;
	q[tail++] = (t_q){m->px, m->py};
	vis[m->py*m->w + m->px] = 1;

	int dirs[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
	while (head<tail){
		t_q cur = q[head++];
		char cell = m->grid[cur.y][cur.x];
		if (cell=='C') rc++;
		if (cell=='E') re=1;
		for (int i=0;i<4;i++){
			int nx=cur.x+dirs[i][0], ny=cur.y+dirs[i][1];
			if (!in_bounds(m,nx,ny)) continue;
			char ncell = m->grid[ny][nx];
			if (ncell=='1') continue;
			int idx = ny*m->w + nx;
			if (!vis[idx]){ vis[idx]=1; q[tail++] = (t_q){nx,ny}; }
		}
	}
	free(q); free(vis);

	if (rc != m->count_c){ err("No se alcanzan todos los C"); return 0; }
	if (!re){ err("No se alcanza la E"); return 0; }
	return 1;
}

static int	push_line(char ***arr, int *cap, int *len, char *line){
	if (*len + 1 >= *cap){
		int ncap = *cap ? *cap * 2 : 8;
		char **tmp = malloc(sizeof(char*) * ncap);
		if (!tmp) return 0;
		for (int i=0; i<*len; i++) tmp[i] = (*arr)[i];
		free(*arr);
		*arr = tmp; *cap = ncap;
    }
	(*arr)[(*len)++] = line;
	(*arr)[*len] = NULL;
	return 1;
}

int	parse_map(const char *path, t_map *m){
	int fd = open(path, O_RDONLY);
	if (fd < 0) return 0;

	char **lines = NULL; int cap = 0, len = 0;
	char *raw;
	while ((raw = get_next_line(fd))){
		raw = strip_nl(raw);
		if (!raw){ close(fd); free_map(m); return 0; }
		if (!push_line(&lines, &cap, &len, raw)){ close(fd); free_map(m); return 0; }
	}
	close(fd);
	if (len == 0){ free(lines); return 0; }

	m->grid = lines;
	m->h = len;
	m->w = (int)slen(lines[0]);
	m->px = m->py = -1;
	m->count_p = m->count_c = m->count_e = 0;

	if (!is_rectangular(m) || !closed_by_walls(m) || !chars_and_counts(m)
		|| !check_path(m)) {
		free_map(m);
		return 0;
	}
	return 1;
}

void	free_map(t_map *m){
	if (!m || !m->grid) return;
	for (int y=0; y<m->h; y++) free(m->grid[y]);
	free(m->grid);
	m->grid = NULL;
}
