/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asolis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/22 05:23:45 by asolis            #+#    #+#             */
/*   Updated: 2017/06/22 05:23:47 by asolis           ###   ########.fr       */
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
