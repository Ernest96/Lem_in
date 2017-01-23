#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "get_next_line.h"
#define AC_R     	"\x1b[31m"
#define AC_G	  	"\x1b[92m"
#define AC_Y	  	"\x1b[33m"
#define AC_B    	"\x1b[34m"
#define AC_M 		"\x1b[35m"
#define AC_C    	"\x1b[36m"
#define AC_RES  	"\x1b[0m"
#define INIT_ATOI int i = 0, nr = 0, n = 0;
#define VAR_INIT_1 t_room *head = NULL; int furn; g_rel = 0; g_tab = NULL;
#define VAR_INIT_2 char *line; int8_t flag = -1; t_room *head = NULL; 
#define INIT_FOR_LIST t_room	*temp, *prev; char	**str; uint8_t x, y;
#define W_S write(1, AC_G, 5); write(1, "##start\n", 8); write(1, AC_RES, 4); 
#define	W_E write(1, AC_C, 5); write(1, "##end\n", 6); write(1, AC_RES, 4);
#define W_F write(1, AC_Y, 5); ft_putnbr(furn); write(1, AC_RES, 4);
#define C_REL char *temp; char **str; t_room *room; int8_t count;
int8_t	g_rel;
int **g_tab;
int *g_path;
char **g_names;
int g_count;
int g_m;
int g_p;
int **g_temp;
int **g_d;
int	g_step;

typedef struct 	s_room
{
	char *name;
	int8_t type;
	uint8_t x;
	uint8_t y;
	struct s_room *next;
}				t_room;

void	ft_init_start_end(t_room **head, char *line, int8_t flag);
void	ft_init_room(t_room **head, char *line);
void	ft_create_array(t_room *room);
void	print_array(void);
t_room *get_farm(int *furn);
int	find_min(int *d, int8_t *marked, int *m);
void	find_path(int **d, int vert, int i, int *m);
void	dijkstra(int **d, int start, int end);
int ft_min(int x, int y);
void	ft_create_d_path();
int8_t ft_first_check(char *line);
void	ft_check_possible(t_room *head);
void	ft_res_array(void);
void	ft_insert(char **str);
void	ft_create_relation(t_room *head, char *line);
void	ft_refresh_node(t_room *temp, char **str, int8_t flag);
void	ft_check_coord(t_room *temp, char *str, int x, int y);
void	ft_free_list(t_room **head);
void	ft_init_node(t_room **temp, char **str);
char **ft_split_check(char *line);
void	ft_free_split(char ***str);
void	ft_init_head(t_room **head, char **str, int8_t flag);
int	ft_strcmp(const char *s1, const char *s2);
void	ft_print_room(t_room *temp);
void	ft_print_farm(int furn, t_room *head);
void	ft_check_command(int8_t *flag, int8_t to_set);
void	ft_reset(t_room *temp, int8_t flag);
char	*ft_strchr(const char *s, int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_atoi_check(const char *str);
void	ft_putnbr(int nb);
void	ft_putchar(char c);
void	ft_error(int n);
void	ft_putstr(char const *s);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_list_push_back(t_list **begin_list, void **tmp, size_t c_size);
t_list	*check_new_line(t_list **head, int flag, const int *fd, int *fd2);
void	restruct_string(t_list **head, char **line);
short	get_line(t_list **head, t_list *final, char **line);
int		get_next_line(int const fd, char **line);
short	is_ok(char c, char ok);
int		get_count(char const *str, char ok);
int		get_size(char const *str, int i, char ok);
char	**ft_strsplit(char const *str, char ok);
