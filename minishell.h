#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "libft/libft.h"
#include <fcntl.h>

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct		s_shll
{
	char			*p_bin;
	char			*p_dir;
	char			*p_name;
	char			*c_wd;
	char			*tmp;
	char			*p_shell;
	char			*path;
	char			*tmp_path;
	char			**mtx;
	char			*direction;
	char			**env;
}					t_shll;

typedef struct		s_axe
{
	int				i;
	int				j;
	size_t			count;
	char			*start;
	char			*end;
	char			*tmp;
}					t_axe;

typedef struct		s_msh
{
	t_shll			sh;
	t_axe			axe;
}					t_msh;

/*
** lists functions used in the proyect.. lists_functions.c
*/
void				ft_lstsearch(t_list *e, char *name);
void				ft_lstaddnth(t_list *e, t_list	*new, int nb);
void				ft_lstedit(t_list *e, char *name, char *value);
void				ft_lstdeletenode(t_list *e, int nb);
char				**ft_lst_to_mtx(t_list *e, t_msh *f);
/*
** cd command functions used in the proyect.. cd_command.c
*/
void				validation_cd_command(char **matrix, t_msh *f, t_list *e);
void				cd_command(char *pwd, t_msh *f, t_list *e, int i);
int					cutting_last_dir(char *path, t_msh *f);
int					simple_path(char *path, t_msh *f);
int					cd(char *path, t_msh *f, char **matrix_path, int i);
/*
** echo command functions used in the proyect.. echo_command.c
*/
void				validation_echo(char **c, t_msh *f, t_list *e);
int					echo(char *c, t_msh *f);
/*
** setenv command functions used in the proyect.. get_env.c
*/
t_list				*get_env(t_msh *f);
void				set_env(t_list *e, char *name, char *value);
void				multi_setenv(t_list *e, char **values, int len, t_msh *f);
void				setenv_validation(t_list *e, char **mtx, t_msh *f);
int					validation_name(char *str);
/*
** unsetenv command functions used in the proyect.. unsetenv.c
*/
void				unsetenv_validation(t_list *e, char **name);
int					unset_env(t_list *e, char *name, int i);
/*
** helper functions used in the proyect.. helper.c helper_2.c
*/
void				ft_error_path(t_msh *f);
void				zap(t_msh *f);
void				ft_putmatrix(char **matrix);
void				ft_printlst(t_list *e);
void				free_shit(char *a, char *b, char *c);
int					ft_matrixlen(char **matrix);
int					ft_memdel_int(void **ap);
int					ft_ismayus(int c);
/*
** main functions used in the proyect.. main.c
*/
void				get_command(char *str, t_msh *f, t_list *e);
void				pre_get_command(char *str, t_msh *f, t_list *e);
int					get_shell(t_msh *f);
/*
** run commands functions used in the proyect.. run_command.c
*/
void				get_path(t_msh *f);	
void				executable(char **mtx, t_msh *f, t_list *e);
int					path_command(char **mtx, t_msh *f, t_list *e);
#endif