/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:34:56 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:35:10 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			unsetenv_validation(t_list *e, char **name)
{
	int			i;

	i = 0;
	if ((i = ft_matrixlen(name)) > 2)
	{
		ft_printfcolor("ERROR: JUST NAME OF VAR_ENV\n", 31);
		return ;
	}
	else if (i == 1)
	{
		ft_printfcolor("ERROR: JUST PUT NAME OF VAR_ENV\n", 31);
		return ;
	}
	else if (i == 2)
		unset_env(e, name[1], 0);
}

int				unset_env(t_list *e, char *name, int i)
{
	t_list		*tmp;
	char		*tamp;
	char		*x;

	tmp = e;
	while (tmp)
	{
		if ((x = ft_strchr(tmp->content, '=')) > 0)
		{
			tamp = ft_strsub(tmp->content, 0,
ft_strlen(tmp->content) - ft_strlen(x));
			if (ft_strcmp(tamp, name) == 0)
			{
				ft_lstdeletenode(e, i + 1);
				return (i);
			}
		}
		i++;
		tmp = tmp->next;
	}
	ft_printfcolor("ERROR: VALUE NOT FOUNDED\n", 31);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tamp);
	return (0);
}
