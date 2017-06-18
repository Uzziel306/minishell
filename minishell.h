#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pwd.h>
#include <uuid/uuid.h>
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
}					t_shll;

typedef struct		s_axe
{
	int				i;
	int				j;
}					t_axe;

typedef struct		s_msh
{
	t_shll			sh;
	t_axe			axe;
}					t_msh;

void		cd_command(char **matrix, t_msh *f);
void		zap(t_msh *f);
void		ft_printlst(t_list *e);
void		ft_putmatrix(char **matrix);
void		ft_error_path(t_msh *f);
t_list		*get_env(void);
void		set_env(t_list *e, char **name);
int			ft_matrixlen(char **matrix);
int			ft_memdel_int(void **ap);
int			cd(char *path, t_msh *f, char **matrix_path, int i);

#endif