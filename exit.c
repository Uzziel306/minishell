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

void	exitazo(t_list *e, t_msh *f)
{
	ft_memdel((void**)&f->sh.p_bin);
	ft_memdel((void**)&f->sh.p_home);
	ft_memdel((void**)&f->sh.p_user);
	ft_memdel((void**)&f);
	ft_lstdel(&e, ft_bzero);
	exit(3);
}
