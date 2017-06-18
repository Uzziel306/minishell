#include "minishell.h"

void			ft_printlst(t_list *e)
{
	t_list		*tmp;

	tmp = e;
	while (tmp)
	{
		ft_printfbasic("%s\n", tmp->content);
		tmp = tmp->next;
	}
}

t_list			*get_env(void)
{
	extern char	**environ;
	t_list		*tmp;
	t_list		*en;
	int			i;

	en = NULL;
	i = 0;

	while (environ[i] != NULL)
	{
		tmp = ft_lstnew(environ[i], ft_strlen(environ[i]) + 1);
		ft_lstaddback(&en, tmp);
		i++;
	}
	return (en);
}

void			set_env(t_list *e, char **name)
{
	char		*tmp;
	char		*tmp2;
	t_list		*env_node;
	if (name[2])
	{
		tmp2 = ft_strjoin(name[1], "=");
		tmp = ft_strjoin(tmp2, name[2]);
		env_node = ft_lstnew(tmp, ft_strlen(tmp));
		ft_lstaddback(&e, env_node);
		ft_memdel((void**)&tmp);
		ft_memdel((void**)&tmp2);
		return ;
	}
	ft_printfbasic("ERROR in name of arguments\n");
}