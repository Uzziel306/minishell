#include "minishell.h"

void		ft_lstaddnth(t_list *e, t_list	*new, int nb)
{
	t_list	*tmp;
	int		i;

	i = -1;
	if (nb == 1)
	{
		new->next = e;
		e = new;
		return ;
	}
	tmp = e;
	while (i < nb - 2)
	{
		tmp = tmp->next;
		i++;
	}
	new->next = tmp->next;
	tmp->next = new;
}

int		cutting_last_dir(char *path, t_msh *f)
{
	char	*tmp;
	char	*j;

	j = ft_strrchr(f->sh.tmp_path, '/');
	tmp = ft_strsub(f->sh.tmp_path, 0, ft_strlen(f->sh.tmp_path) - ft_strlen(j));
	if (access(tmp, F_OK) == -1)
	{
		ft_memdel((void**)&tmp);
		ft_printfbasic("-bash: cd: %s: No such file or directory\n", path);
		return (0);
	}
	f->sh.tmp_path = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	return(1);
}

int			simple_path(char *path, t_msh *f)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_strjoin("/", path);
	tmp = ft_strjoin(f->sh.tmp_path, tmp2);
	if (access(tmp, F_OK) == -1)
	{
		ft_error_path(f);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		return (0);
	}
	f->sh.tmp_path = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	return (1);
}

int			cd(char *path, t_msh *f, char **matrix_path, int i)
{
	if (ft_strchr(path, '/'))
	{
		matrix_path = ft_strsplit(path, '/');
		while (matrix_path[i] != NULL)
		{
			if (ft_strcmp(matrix_path[i], "..") == 0)
				{
					if(!cutting_last_dir(matrix_path[i], f))
						return(ft_memdel_int((void**)&matrix_path));
				}
			else if(!(simple_path(matrix_path[i], f)))
				return(ft_memdel_int((void**)&matrix_path));
			i++;
		}
		ft_memdel_int((void**)&matrix_path);
	}
	else if (ft_strcmp(path, "..") == 0)
		{
			if(!cutting_last_dir(path, f))
				return(0);
		}
	else if (!simple_path(path, f))
		return(0);
	return(1);
}

void		validation_cd_command(char **matrix, t_msh *f, t_list *e)
{
	int		i;
	t_list	*lst_tmp;

	if (ft_matrixlen(matrix) == 1)
	{
		f->sh.path = ft_strdup(f->sh.p_dir);
		i = unset_env(e, "PWD", 0);
		lst_tmp = ft_lstnew("PWD=/nfs/2016/a/asolis", 23);
		ft_lstaddnth(e, lst_tmp, i);
	}
	else if (ft_matrixlen(matrix) == 2)
		cd_command(matrix[1], f, e, 0);
	else if (ft_matrixlen(matrix) >= 3)
		ft_printfcolor("ERROR: TOO MANY ARGUMENTS\n", 31);
}

void		ft_lstedit(t_list *e, char *name, char *value)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	t_list	*lst_tmp;

	i = unset_env(e, name, 0);
	tmp = ft_strjoin(name, "=");
	tmp2 = ft_strjoin(tmp, value);
	lst_tmp = ft_lstnew(tmp2, ft_strlen(tmp2) + 1);
	ft_lstaddnth(e, lst_tmp, i);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
}

void		cd_command(char *pwd, t_msh *f, t_list *e, int i)
{
	char	**mtrx;
	char	*old_pwd;

	f->sh.direction = ft_strdup(pwd);
	f->sh.tmp_path = ft_strdup(f->sh.path);
	old_pwd = ft_strdup(f->sh.tmp_path);
		if (cd(pwd, f, mtrx, i))
		{
			f->sh.path = ft_strdup(f->sh.tmp_path);
			chdir(f->sh.path);
			ft_lstedit(e, "PWD", f->sh.path);
			ft_lstedit(e, "OLDPWD", old_pwd);
		}
}