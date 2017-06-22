#include "minishell.h"

int				echo(char *c, t_msh *f)
{
	int i;

	i = 0;
	while (c[i] != '\0')
	{
		if (c[i] == '\\' && c[i + 1] == 'c')
			return (0);
		if (c[i] == '\\' && c[i + 1] == 'n')
		{
			ft_printfbasic("\n");
			i++;
		}
		else
			ft_putchar(c[i]);
		i++;
	}
	return (1);
}

void		validation_echo(char **c, t_msh *f, t_list *e)
{
	int		i;
	char	*tmp;
	t_list	*tmp_node;

	tmp_node = e;
	i = 0;
	while (c[++i] != NULL)
	{
		if (i > 1)
			ft_printfbasic(" ");
		if (c[i][0] == '$')
		{
			tmp = ft_strsub(c[i], 1, ft_strlen(c[i]));
			if (validation_name(tmp))
				ft_lstsearch(e, tmp);
		}
		else if (!echo(c[i], f))
			return ;
	}
	ft_printfbasic("\n");
}
