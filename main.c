#include "minishell.h"

void					get_command(char *str, t_msh *f, t_list *e)
{
	char				**matrix;

	matrix = ft_strsplit(str, ' ');
	if (matrix[0][0] == '.' && matrix[0][1] == '/')
		executable(matrix, f, e);
	else if (ft_strcmp(matrix[0], "pwd") == 0)
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

int					get_shell(t_msh *f)
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

void				pre_get_command(char *str, t_msh *f, t_list *e)
{
	char			*i;
	char			**multi_cmd;
	int				j;

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

int					main(void)
{
	char			*command;
	t_msh			*f;
	t_list			*e;

	f = (t_msh*)malloc(sizeof(t_msh));
	zap(f);
	e = get_env(f);
	get_shell(f);
	while (42)
	{
		//TERMINAR LA LISTA.
		ft_printfcolor("%s%s%s", "@", 33, f->sh.p_name, 33, "$>", 33);
		get_next_line(0, &command);
		if (ft_strlen(command))
			pre_get_command(command, f, e);
	}
	ft_memdel((void**)&command);
	ft_memdel((void**)&f);
	ft_lstdel(&e, ft_bzero);
	return (1);
}
