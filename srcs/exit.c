/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:19:36 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:20:11 by asolis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exitazo(t_list *e, t_msh *f, char **mtx,  char *line)
{
	ft_memdel((void**)&mtx);
	ft_memdel((void**)&f->sh.p_bin);
	ft_memdel((void**)&f->sh.p_dir);
	ft_memdel((void**)&f->sh.p_name);
	ft_memdel((void**)&f->sh.c_wd);
	ft_memdel((void**)&f->sh.p_shell);
	ft_memdel((void**)&f->sh.path);
	ft_memdel((void**)&f->sh.tmp_path);
	ft_memdel((void**)&f->sh.mtx);
	ft_memdel((void**)&f->sh.env);
	ft_memdel((void**)&f);
	ft_memdel((void**)&line);
	ft_lstdel(&e, ft_bzero);
	exit(0);
}
