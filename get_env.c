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
	free(tmp);
}

int			ft_ismayus(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

void			ft_lstdeletenode(t_list *e, int nb)
{
	t_list		*tmp;
	t_list		*tmp2;
	int			i;

	i = -1;
	tmp = e;
	if (nb == 1)
	{
		e = tmp->next;
		free(tmp);
		return ;
	}
	while (++i < nb - 2)
		tmp = tmp->next;
	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	free(tmp2);
}

t_list			*get_env(t_msh *f)
{
	extern char	**environ;
	t_list		*tmp;
	t_list		*en;
	int			i;
	char		*path;

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

int			unset_env(t_list *e, char *name, int i)
{
	t_list		*tmp;
	char		*tamp;
	char		*x;

	tmp = e;
	while (tmp)
	{
		if ((x = ft_strchr(tmp->content, '=')) > 0)
		{
			tamp = ft_strsub(tmp->content, 0, ft_strlen(tmp->content) - ft_strlen(x));
			if (ft_strcmp(tamp, name) == 0)
			{
				ft_lstdeletenode(e, i + 1);
				return (i);
			}
		}
		i++;
		tmp = tmp->next;
	}
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tamp);
	return (0);
}

void			set_env(t_list *e, char *name, char *value)
{
	char		*tmp;
	char		*tmp2;
	t_list		*env_node;

	tmp2 = ft_strjoin(name, "=");
	tmp = ft_strjoin(tmp2, value);
	env_node = ft_lstnew(tmp, ft_strlen(tmp) + 1);
	ft_lstaddback(&e, env_node);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&tmp2);
}

int				validation_name(char *str)
{
	int			i;

	i = -1;
	while (str[++i])
	{
		if (!ft_ismayus(str[i]))
			return (0);
	}
	return (1);
}

void			multi_setenv(t_list *e, char **values, int len, t_msh *f)
{
	int			i;
	size_t		cont;

	f->axe.start = ft_strsub(values[2], 1, ft_strlen(values[2]));
	f->axe.end = ft_strsub(values[len - 1], 0, ft_strlen(values[len - 1]) - 1);
	i = 2;
	cont = ft_strlen(f->axe.start);
	cont += ft_strlen(f->axe.end);
	while (values[++i + 1] != NULL)
		cont += ft_strlen(values[i]);
	cont += len - 2;
	i = 2;
	f->axe.tmp = (char*)malloc(sizeof(char) * (cont));
	f->axe.tmp = ft_strcat(f->axe.tmp, f->axe.start);
	f->axe.tmp = ft_strcat(f->axe.tmp, ":");
	while (values[++i + 1] != NULL)
	{
		f->axe.tmp = ft_strcat(f->axe.tmp, values[i]);
		f->axe.tmp = ft_strcat(f->axe.tmp, ":");
	}
	f->axe.tmp = ft_strcat(f->axe.tmp, f->axe.end);
	set_env(e, values[1], f->axe.tmp);
}

void			setenv_validation(t_list *e, char **mtx, t_msh *f)
{
	int			i;

	i = 0;
	if ((i = ft_matrixlen(mtx)) == 1)
		ft_printlst(e);
	else if (!validation_name(mtx[1]))
		ft_printfcolor("%s\n", "ERROR: THE NAME SHALL BE IN MAYUS", 31);
	else if (i == 3)
		set_env(e, mtx[1], mtx[2]);
	else if (i > 3)
	{
		if (mtx[2][0] == '(' && mtx[i - 1][ft_strlen(mtx[i - 1])- 1] == ')')
			multi_setenv(e, mtx, i, f);
		else
			ft_printfcolor("%s\n", "ERROR: FOR MULTI VALUES USE '(value1 value2 ...)'\n", 31);
	}
}

