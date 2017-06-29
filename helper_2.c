/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:23:45 by asolis            #+#    #+#             */
/*   Updated: 2017/06/28 17:49:25 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_memdel_int(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
	return (0);
}

int			ft_ismayus(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void		free_shit(char *a, char *b, char *c)
{
	ft_memdel((void**)&a);
	ft_memdel((void**)&b);
	ft_memdel((void**)&c);
}

void		cd_command_len_1(t_msh *f, t_list *e)
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

char		*get_path(t_list *e)
{
	char	*tmp_path;
	char	*tmp_pwd;
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		tmp_path = ft_strsub(tmp->content, 0, 4);
		if (ft_strcmp(tmp_path, "PATH") == 0)
		{
			tmp_pwd = ft_strsub(tmp->content, 5, ft_strlen(tmp->content));
			return (tmp_pwd);
		}
		ft_memdel((void**)&tmp_path);
		tmp = tmp->next;
	}
	free(tmp);
	return (0);
}
