#include "minishell.h"

int				echo(char **c, t_msh *f)
{
	zap(f);
	while (c[f->axe.i] != NULL)
	{
		if (f->axe.i > 1)
			ft_printfbasic(" ");
		while (c[f->axe.i][f->axe.j] != '\0')
		{
			if (c[f->axe.i][f->axe.j] == '\\' && c[f->axe.i][f->axe.j + 1] == 'c')
				return (0);
			if (c[f->axe.i][f->axe.j] == '\\' && c[f->axe.i][f->axe.j + 1] == 'n')
			{
				ft_printfbasic("\n");
				f->axe.j += 1;
			}
			else
				ft_putchar(c[f->axe.i][f->axe.j]);
			f->axe.j += 1;
		}
		f->axe.j = 0;
		f->axe.i += 1;
	}
	ft_printfbasic("\n");
	return (0);
}

void		validation_echo(char **c, t_msh *f)
{
	int		i;

	i 
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

static int			forkzazo(char **matrix, t_list *e, t_msh *f)
{
	pid_t	pid;
	char	*path;

	f->sh.env = ft_lst_to_mtx(e, f);
	// ft_putmatrix(f->sh.env);
	pid = fork();
	if (pid == -1)
		printf("error\n");
	if (pid == 0)
	{
		if (execve("/bin/ls", matrix, f->sh.env) != -1)
		return (0);
	}

	if (pid > 0)
		pid = wait(0);
	return (0);
}

void		get_command(char *str, t_msh *f, t_list *e)
{
	char	**matrix;

		matrix = ft_strsplit(str, ' ');
		if (ft_strcmp(matrix[0], "pwd") == 0)
			ft_printfcolor("%s\n", f->sh.path, 34);
		else if (ft_strcmp(matrix[0], "exit") == 0)
			exit (0);
		else if (ft_strcmp(matrix[0], "echo") == 0)
			echo(matrix, f);
		else if (ft_strcmp(matrix[0], "ls") == 0)
				forkzazo(matrix, e, f);
		else if (ft_strcmp(matrix[0], "cd") == 0)
			validation_cd_command(matrix, f, e);
		else if (ft_strcmp(matrix[0], "env") == 0)
			ft_printlst(e);
		else if (ft_strcmp(matrix[0], "setenv") == 0)
			setenv_validation(e, matrix, f);
		else if (ft_strcmp(matrix[0], "unsetenv") == 0)
			unsetenv_validation(e, matrix);
		else
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

int			main(int ac, char **argv, char **env)
{
	int				i;
	char			*command;
	char			*buf;
	t_msh			*f;
	t_list			*e;
	t_list			*head;

	f = (t_msh*)malloc(sizeof(t_msh));
	zap(f);
	get_shell(f);
	e = get_env(f);
	while(42)
	{
		//ARREGLAR ENV CON EL CD COMMAND 1.1
		ft_printfcolor("%s%s%s", "@", 33, f->sh.p_name, 33, "$>", 33);
		get_next_line(0, &command);
		if (ft_strlen(command))
			get_command(command, f, e);
	}
	ft_memdel((void**)&f);
	ft_memdel((void**)&e);
	return (1);
}
