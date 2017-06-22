#include "minishell.h"

void		get_path(t_msh *f)
{
	extern	char	**environ;
	int				i;

	i = 0;
	while(environ[i] != NULL)
	{
		if (environ[i][4])
		{
			if (environ[i][0] == 'P' && environ[i][1] == 'A' &&
				environ[i][2] == 'T' && environ[i][3] == 'H')
				f->sh.p_bin = ft_strsub(environ[i], 5, ft_strlen(environ[i]));
		}
		i++;
	}
}

static int			forkzazo(char **matrix, t_list *e, t_msh *f, char *path)
{
	pid_t	pid;

	if (f->sh.env != NULL)
		f->sh.env = ft_lst_to_mtx(e, f);
	else
	{
		ft_memdel((void**)&f->sh.env);
		f->sh.env = ft_lst_to_mtx(e, f);
	}
	pid = fork();
	if (pid == -1)
		ft_printfcolor("ERROR: RUNING\n", 31);
	if (pid == 0)
	{
		if (execve(path, matrix, f->sh.env) != -1)
		return (0);
	}
	if (pid > 0)
		pid = wait(0);
	return (0);
}

int		path_command(char **mtx, t_msh *f, t_list *e)
{
	int		i;
	char	**path_mtx;
	char	*tmp;
	char	*tmp2;


	i = -1;
	path_mtx = ft_strsplit(f->sh.p_bin, ':');
	while (path_mtx[++i])
	{
		tmp2 = ft_strjoin(path_mtx[i], "/");
		tmp = ft_strjoin(tmp2, mtx[0]);
		if (access(tmp, X_OK) == 0)
		{
			forkzazo(mtx, e, f, tmp);
			ft_memdel((void**)&tmp);
			ft_memdel((void**)&tmp2);
			return (1);
		}
	}
	return (0);
}

void		executable(char **mtx, t_msh *f, t_list *e)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp2 = ft_strsub(mtx[0], 2, ft_strlen(mtx[0]));
	tmp3 = ft_strjoin(f->sh.path, "/");
	tmp = ft_strjoin(tmp3, tmp2);
	forkzazo(mtx, e, f, tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	ft_memdel((void**)&tmp3);
}