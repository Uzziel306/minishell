#include "minishell.h"

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

void		cd_command(char **matrix, t_msh *f)
{
	int		i;
	char	**mtrx;

	i = 0;
	if (ft_matrixlen(matrix) == 1)
	{
		f->sh.path = ft_strdup(f->sh.p_dir);
		return ;
	}
	f->sh.direction = ft_strdup(matrix[1]);
	f->sh.tmp_path = ft_strdup(f->sh.path);
	if (ft_matrixlen(matrix) > 1)
	{
		if (cd(matrix[1], f, mtrx, i))
			f->sh.path = ft_strdup(f->sh.tmp_path);
	}
}