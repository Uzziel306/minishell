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