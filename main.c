#include "minishell.h"

int				echo(char *c, t_msh *f)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\\' && c[i + 1] == 'c')
			return (0);
		if (c[i] == '\\' && c[i + 1] == 'n')
			ft_printfbasic("\n");
		else
			ft_putchar(c[i]);
		i++;
	}
	return (0);
}

void		ft_lstsearch(t_list *e, char *name)
{
	t_list	*tmp;
	char	*i;
	char	*tamp;
	char	*res;

	tmp = e;
	while (tmp)
	{
		if ((i = ft_strchr(tmp->content, '=')))
		{
			tamp = ft_strsub(tmp->content, 0,  ft_strlen(tmp->content) - ft_strlen(i));
			if (ft_strcmp(tamp, name) == 0)
			{
				res = ft_strsub(tmp->content, ft_strlen(name) + 1, ft_strlen(i));
				ft_printfbasic("%s", res);
				ft_memdel((void**)&res);
			}
			ft_memdel((void**)&tamp);
		}
		tmp = tmp->next;
	}
	free (tmp);
}

void		validation_echo(char **c, t_msh *f, t_list *e)
{
	int		i;
	char	*tmp;
	t_list	*tmp_node;

	tmp_node = e;
	i = 0;
	while (c[++i] != NULL)
	{
		if (i > 1)
			ft_printfbasic(" ");
		if (c[i][0] == '$')
		{
			tmp = ft_strsub(c[i], 1, ft_strlen(c[i]));
			if (validation_name(tmp))
				ft_lstsearch(e, tmp);
		}
		else if (!echo(c[i], f))
			return ;
	}
	ft_printfbasic("\n");
}

char		**ft_lst_to_mtx(t_list *e, t_msh *f)
{
	int		i;
	t_list	*tmp;
	char	**mtx;

	i = 0;
	tmp = e;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	mtx = (char**)malloc(sizeof(char*) * (i + 1));
	tmp = e;
	mtx[i] = NULL;
	while (tmp)
	{
		mtx[--i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (mtx);
}

static int			forkzazo(char **matrix, t_list *e, t_msh *f, char *path)
{
	pid_t	pid;

	f->sh.env = ft_lst_to_mtx(e, f);
	// ft_putmatrix(f->sh.env);
	pid = fork();
	if (pid == -1)
		printf("error\n");
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

void		get_command(char *str, t_msh *f, t_list *e)
{
	char	**matrix;
	int		i;

	i = 0;
	matrix = ft_strsplit(str, ' ');
	if (ft_strcmp(matrix[0], "pwd") == 0)
		ft_printfcolor("%s\n", f->sh.path, 34);
	else if (ft_strcmp(matrix[0], "exit") == 0)
		exit (0);
	else if (ft_strcmp(matrix[0], "echo") == 0)
		validation_echo(matrix, f, e);
	else if (ft_strcmp(matrix[0], "cd") == 0)
		validation_cd_command(matrix, f, e);
	else if (ft_strcmp(matrix[0], "env") == 0)
		ft_printlst(e);
	else if (ft_strcmp(matrix[0], "setenv") == 0)
		setenv_validation(e, matrix, f);
	else if (ft_strcmp(matrix[0], "unsetenv") == 0)
		unsetenv_validation(e, matrix);
	else if (!path_command(matrix, f, e))
		ft_printfcolor("%s %s\n", matrix[0], 31, ": command not found", 31);
	ft_memdel((void**)&matrix);
}

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

int		get_shell(t_msh *f)
{
	struct stat		stat;
	struct passwd	*pw;

	if (lstat(".", &stat) == -1)
		return (0);
	if ((pw = getpwuid(stat.st_uid)) == NULL)
		return (0);
	get_path(f);
	f->sh.p_dir = ft_strdup(pw->pw_dir);
	f->sh.p_name = ft_strdup(pw->pw_name);
	f->sh.c_wd = ft_strdup(getcwd(NULL, 0));
	f->sh.p_shell = ft_strdup(pw->pw_shell);
	f->sh.path = ft_strdup(f->sh.c_wd);
	return (0);
}

void		pre_get_command(char *str, t_msh *f, t_list *e)
{
	char	*i;
	char	**multi_cmd;
	int		j;

	j = -1;
	if ((i = ft_strchr(str, ';')))
	{
		multi_cmd = ft_strsplit(str, ';');
		while (multi_cmd[++j])
			get_command(multi_cmd[j], f, e);
		ft_memdel((void**)&multi_cmd);
	}
	else
		get_command(str, f, e);
}

int			main(int ac, char **argv, char **env)
{
	char			*command;
	t_msh			*f;
	t_list			*e;

	f = (t_msh*)malloc(sizeof(t_msh));
	zap(f);
	get_shell(f);
	e = get_env(f);
	while(42)
	{
		//TERMINAR LA LISTA.
		ft_printfcolor("%s%s%s", "@", 33, f->sh.p_name, 33, "$>", 33);
		get_next_line(0, &command);
		if (ft_strlen(command))
			pre_get_command(command, f, e);
	}
	ft_memdel((void**)&f);
	ft_memdel((void**)&e);
	return (1);
}
