/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:15:05 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:18:27 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			cutting_last_dir(char *path)
{
	char	*tmp;
	char	*j;

	j = ft_strrchr(getcwd(NULL, 0), '/');
	tmp = ft_strsub(getcwd(NULL, 0), 0, ft_strlen
(getcwd(NULL, 0)) - ft_strlen(j));
	if (ft_strlen(tmp) == 0)
	{
		chdir("/");
		return (1);
	}
	if (chdir(tmp) == -1)
	{
		ft_memdel((void**)&tmp);
		ft_printfbasic("-bash: cd: %s: No such file or directory\n", path);
		return (0);
	}
	chdir(tmp);
	ft_memdel((void**)&tmp);
	return (1);
}

int			simple_path(char *path, t_msh *f)
{
	char	*tmp;
	char	*tmp2;

	if (ft_strcmp(path, "~") == 0)
	{
		chdir(f->sh.p_home);
		return (1);
	}
	if (ft_strcmp(".", path) == 0)
		return (0);
	tmp2 = ft_strjoin("/", path);
	tmp = ft_strjoin(getcwd(NULL, 0), tmp2);
	if (chdir(tmp) == -1)
	{
		ft_error_path(tmp);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		return (0);
	}
	chdir(tmp);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
	return (1);
}

int			cd(char *path, char **matrix_path, int i, t_msh *f)
{
	if (ft_strchr(path, '/'))
	{
		matrix_path = ft_strsplit(path, '/');
		while (matrix_path[i] != NULL)
		{
			if (ft_strcmp(matrix_path[i], "..") == 0)
			{
				if (!cutting_last_dir(matrix_path[i]))
					return (ft_memdel_int((void**)&matrix_path));
			}
			else if (!(simple_path(matrix_path[i], f)))
				return (ft_memdel_int((void**)&matrix_path));
			i++;
		}
		ft_memdel_int((void**)&matrix_path);
	}
	else if (ft_strcmp(path, "..") == 0)
	{
		if (!cutting_last_dir(path))
			return (0);
	}
	else if (!simple_path(path, f))
		return (0);
	return (1);
}

void		validation_cd_command(char **matrix, t_msh *f, t_list *e)
{
	if (general(matrix[1], e))
		return ;
	else if (ft_matrixlen(matrix) == 1)
		cd_command_len_1(f, e);
	else if (ft_strcmp(matrix[1], "/") == 0)
		cd_command_home(f, e);
	else if (ft_strcmp(matrix[1], "-") == 0)
		cd_command_minus(e);
	else if (ft_matrixlen(matrix) == 2)
		cd_command(matrix[1], e, 0, f);
	else if (ft_matrixlen(matrix) >= 3)
		ft_printfcolor("ERROR: TOO MANY ARGUMENTS\n", 31);
}

void		cd_command(char *pwd, t_list *e, int i, t_msh *f)
{
	char	**mtrx;
	char	*old_pwd;

	mtrx = NULL;
	old_pwd = ft_strdup(getcwd(NULL, 0));
	if (cd(pwd, mtrx, i, f))
	{
		ft_lstedit(e, "PWD", getcwd(NULL, 0));
		ft_lstedit(e, "OLDPWD", old_pwd);
	}
	ft_memdel((void**)&old_pwd);
}
