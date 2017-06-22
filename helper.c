#include "minishell.h"

void		ft_error_path(t_msh *f)
{
	ft_printfbasic("-bash: cd: ");
	ft_printfbasic("%s", f->sh.direction);
	ft_printfbasic(": No such file or directory\n");
}

void		zap(t_msh *f)
{
	f->axe.j = 0;
	f->axe.i = 1;
}

int			ft_matrixlen(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

void		ft_putmatrix(char **matrix)
{
	int		i;

	i = -1;
	while (matrix[++i] != NULL)
		ft_printfbasic("%s\n", matrix[i]);
}

void		ft_printlst(t_list *e)
{
	t_list	*tmp;

	tmp = e;
	while (tmp)
	{
		ft_printfbasic("%s\n", tmp->content);
		tmp = tmp->next;
	}
	free(tmp);
}