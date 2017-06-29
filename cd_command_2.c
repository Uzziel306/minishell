/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 17:53:15 by asolis            #+#    #+#             */
/*   Updated: 2017/06/28 17:53:16 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			general(char *direction, t_list *e)
{
	char	*old_pwd;

	old_pwd = ft_strdup(getcwd(NULL, 0));
	if ((chdir(direction)) == 0)
	{
		ft_lstedit(e, "PWD", direction);
		ft_lstedit(e, "OLDPWD", old_pwd);
		ft_memdel((void**)&old_pwd);
		return (1);
	}
	ft_memdel((void**)&old_pwd);
	return (0);
}

void		cd_command_minus(t_list *e)
{
	char	*tmp_pwd;
	char	*new_pwd;
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		tmp_pwd = ft_strsub(tmp->content, 0, 6);
		if (ft_strcmp(tmp_pwd, "OLDPWD") == 0)
		{
			new_pwd = ft_strsub(tmp->content, 7, ft_strlen(tmp->content));
			if (chdir(new_pwd) == 0)
				ft_memdel((void**)&new_pwd);
		}
		ft_memdel((void**)&tmp_pwd);
		tmp = tmp->next;
	}
	free(tmp);
}

void		cd_command_home(t_msh *f, t_list *e)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strdup(getcwd(NULL, 0));
	new_pwd = ft_strdup(f->sh.p_home);
	if ((chdir(new_pwd)) == 0)
	{
		ft_lstedit(e, "PWD", new_pwd);
		ft_lstedit(e, "OLDPWD", old_pwd);
	}
	ft_memdel((void**)&old_pwd);
	ft_memdel((void**)&new_pwd);
}
