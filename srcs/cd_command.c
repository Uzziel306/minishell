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

int			cutting_last_dir(char *path, t_msh *f)
{
	char	*tmp;
	char	*j;

	if (ft_strcmp(f->sh.tmp_path, "/nfs") == 0)
	{
		f->sh.tmp_path = ft_strdup("/");
		return (1);
	}
	j = ft_strrchr(f->sh.tmp_path, '/');
	tmp = ft_strsub(f->sh.tmp_path, 0, ft_strlen
(f->sh.tmp_path) - ft_strlen(j));
	if (chdir(tmp) == -1)
	{
		ft_memdel((void**)&tmp);
		ft_printfbasic("-bash: cd: %s: No such file or directory\n", path);
		return (0);
	}
	f->sh.tmp_path = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	return (1);
}

int			simple_path(char *path, t_msh *f)
{
	char	*tmp;
	char	*tmp2;

	if (ft_strcmp(".", path) == 0)
		return (0);
	if (ft_strcmp(f->sh.tmp_path, "/") == 0)
	{
		if (ft_strcmp(path, "nfs") == 0)
		f->sh.tmp_path = ft_strdup("/nfs");
		return (1);
	}
	tmp2 = ft_strjoin("/", path);
	tmp = ft_strjoin(f->sh.tmp_path, tmp2);
	if (chdir(tmp) == -1)
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
				if (!cutting_last_dir(matrix_path[i], f))
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
		if (!cutting_last_dir(path, f))
			return (0);
	}
	else if (!simple_path(path, f))
		return (0);
	return (1);
}

void		validation_cd_command(char **matrix, t_msh *f, t_list *e)
{
	char	*old_pwd;

	if (ft_matrixlen(matrix) == 1)
	{
		old_pwd = ft_strdup(f->sh.path);
		f->sh.path = ft_strdup(f->sh.p_dir);
		chdir(f->sh.path);
		ft_lstedit(e, "PWD", f->sh.path);
		ft_lstedit(e, "OLDPWD", old_pwd);
		ft_memdel((void**)&old_pwd);
	}
	if (ft_strcmp(matrix[1], "/") == 0)
	{
		old_pwd = ft_strdup(f->sh.path);
		f->sh.path = ft_strdup("/");
		chdir(f->sh.path);
		ft_lstedit(e, "PWD", f->sh.path);
		ft_lstedit(e, "OLDPWD", old_pwd);
		ft_memdel((void**)&old_pwd);
	}
	else if (ft_matrixlen(matrix) == 2)
		cd_command(matrix[1], f, e, 0);
	else if (ft_matrixlen(matrix) >= 3)
		ft_printfcolor("ERROR: TOO MANY ARGUMENTS\n", 31);
}

void		cd_command(char *pwd, t_msh *f, t_list *e, int i)
{
	char	**mtrx;
	char	*old_pwd;

	mtrx = NULL;
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
	ft_memdel((void**)&old_pwd);
}
