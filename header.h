# ifndef HEADER_H
# define HEADER_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "get_next_line.h"
#define AC_R     		"\x1b[31m"
#define AC_G	  		"\x1b[92m"
#define AC_Y	  		"\x1b[33m"
#define AC_B    		"\x1b[34m"
#define AC_M 			"\x1b[35m"
#define AC_C    		"\x1b[36m"
#define AC_RES  		"\x1b[0m"
#define INIT_ATOI 		int i = 0, nr = 0, n = 0;
#define VAR_INIT_1 		t_room *head = NULL; int furn; g_rel = 0; g_tab = NULL;
#define VAR_INIT_2 		char *line; int8_t flag = -1; t_room *head = NULL; 
#define INIT_FOR_LIST 	t_room	*temp, *prev; char	**str; uint8_t x, y;
#define W_S1 			write(1, AC_G, 5); write(1, "##start\n", 8);
#define W_S 			W_S1 write(1, AC_RES, 4);
#define	W_E1 			write(1, AC_C, 5); write(1, "##end\n", 6);
#define W_E 			W_E1 write(1, AC_RES, 4);
#define W_F1 			write(1, AC_Y, 5); ft_putnbr(furn); 
#define W_F 			W_F1 write(1, AC_RES, 4);
#define C_REL 			char *temp; char **str; t_room *room; int8_t count;
#define F11 			*furn = ft_atoi_check(line); if (!(*furn)) ft_error();
#define F1 				F11 flag = 0;
#define RE12 			{ ft_refresh_node(temp, str, flag);
#define RE1 			RE12 ft_free_split(&str); return ; }
#define RE22 			{ ft_refresh_node(temp, str, 0); ft_free_split(&str);
#define RE2 			RE22 return ; }
#define INIT_DIJKSTRA1 	int *m = get_m(); int v; int k = -1; int i = -1;
#define INIT_DIJKSTRA 	INIT_DIJKSTRA1 int8_t *marked = get_marked(); g_m = 0;
#define FA 				int i = 1, k = -1, j, m, **found_path = NULL;
#define TA  			int n, **temp_path = *paths, flag2 = 0;
#define FS1 			int i, step = 0, j, f_temp = furn, n = 1, *sim;
#define FS2 			FS1 sim = (int*)malloc(sizeof(int) * g_count);
#define FS 				FS2 reset_sim(sim);
#define C11 			sim[paths[i][j + 1]]++;
#define C12 			C11	g_pos[paths[i][j + 1]] = g_pos[paths[i][j]];
#define C13 			C12 if (param == 1) ft_put_change(paths[i][j + 1]);
#define C1 				C13 sim[paths[i][j]] = 0;
#define C21 			sim[paths[i][j + 1]] = i + 1;
#define C22 			C21 g_pos[paths[i][j + 1]] = g_pos[paths[i][j]];
#define C23 			C22 if (param == 1) ft_put_change(paths[i][j + 1]);
#define C2 				C23 sim[paths[i][j]] = 0;
#define C31 			if (paths[i][2] != end) sim[paths[i][2]] = i + 1;
#define C32 C31 		else sim[end]++; g_pos[paths[i][2]] = n;
#define C33 C32 		if (param == 1) ft_put_change(paths[i][2]);
#define C3  C33  		--furn; ++n;
#define TO_PRINT 		if (param == 1) ft_putchar('\n'); ++step;
#define CHECK1  		if ((furn >= paths[i][0] - paths[0][0]) && furn)
#define CHECK2  		CHECK1 if (sim[paths[i][2]] == 0 || paths[i][2] == end)
#define CHECK 			CHECK2 { C3; }

int8_t					g_rel;
int 					**g_tab;
int 					*g_path;
char 					**g_names;
int 					g_count;
int 					g_m;
int 					g_p;
int 					**g_temp;
int 					**g_d;
int						g_step;
int 					*g_pos;

typedef struct 			s_room
{
	char 	*name;
	int8_t 	type;
	uint8_t	x;
	uint8_t y;
	struct 	s_room *next;
}						t_room;

void					ft_init_start_end(t_room **head, char *line,
						int8_t flag);
void					ft_init_room(t_room **head, char *line);
void					ft_create_array(t_room *room);
void					print_array(void);
t_room 					*get_farm(int *furn);
int						find_min(int *d, int8_t *marked, int *m);
void					find_path(int **d, int vert, int i, int *m);
int 					ft_min(int x, int y);
void					ft_create_d_path();
int8_t 					ft_first_check(char *line);
void					ft_check_possible(t_room *head);
void					ft_res_array(void);
void					ft_insert(char **str);
void					ft_create_relation(t_room *head, char *line);
void					ft_refresh_node(t_room *temp, char **str,
						int8_t flag);
void					ft_check_coord(t_room *temp, char *str, int x,
						int y);
void					ft_free_list(t_room **head);
void					ft_init_node(t_room **temp, char **str);
char 					**ft_split_check(char *line);
void					ft_free_split(char ***str);
void					ft_init_head(t_room **head, char **str, int8_t flag);
int						ft_strcmp(const char *s1, const char *s2);
void					ft_print_room(t_room *temp);
void					ft_print_farm(int furn, t_room *head);
void					ft_check_command(int8_t *flag, int8_t to_set);
void					ft_reset(t_room *temp, int8_t flag);
char					*ft_strchr(const char *s, int c);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *src);
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_atoi_check(const char *str);
void					ft_putnbr(int nb);
void					ft_putchar(char c);
void					ft_error(void);
void					ft_putstr(char const *s);
size_t					ft_strlen(const char *str);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					ft_list_push_back(t_list **begin_list, void **tmp,
						size_t c_size);
t_list					*check_new_line(t_list **head, int flag, const int *fd,
						int *fd2);
void					restruct_string(t_list **head, char **line);
short					get_line(t_list **head, t_list *final, char **line);
int						get_next_line(int const fd, char **line);
short					is_ok(char c, char ok);
int						get_count(char const *str, char ok);
int						get_size(char const *str, int i, char ok);
char					**ft_strsplit(char const *str, char ok);
void					ft_get_start_end(t_room *head, int *start, int *end,
						int i);
int						find_min(int *d, int8_t *marked, int *m);
void					find_path(int **d, int vert, int i, int *m);
int 					*get_m(void);
int8_t 					*get_marked(void);
void					dijkstra(int **d, int start, int end);
int						ft_check_solution_1(int start, int end, int *path);
int						ft_check_solution_2(int start, int end, int *path);
int						**ft_init_path(int start);
void					reset_sim(int *sim);
void					ft_put_change(int coord);
int 					**find_another(int **paths, int start, int end);
void 					mark_node(int **paths, int option, int to_mark,
						int prev);
void 					copy_back(void);
int						try_all(int ***paths, int furn, int start, int end);
void					delete_node(int **paths);
void					add_path(int **paths, int start, int end);
void					lem_in(int start, int end, int furn);
int						ft_simulate(int **paths, int furn, int end, int8_t param);
# endif
