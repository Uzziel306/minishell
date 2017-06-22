void		ft_lstsearch(t_list *e, char *name)
{
	t_list	*tmp;
	char	*i;
	char	*tamp;
	char	*res;

	tmp = e;
	while (tmp)
	{
		if ((i = ft_strchr(tmp->content, '=')))
		{
			tamp = ft_strsub(tmp->content, 0,  ft_strlen(tmp->content) - ft_strlen(i));
			if (ft_strcmp(tamp, name) == 0)
			{
				res = ft_strsub(tmp->content, ft_strlen(name) + 1, ft_strlen(i));
				ft_printfbasic("%s", res);
				ft_memdel((void**)&res);
			}
			ft_memdel((void**)&tamp);
		}
		tmp = tmp->next;
	}
	free (tmp);
}

char		**ft_lst_to_mtx(t_list *e, t_msh *f)
{
	int		i;
	t_list	*tmp;
	char	**mtx;

	i = 0;
	tmp = e;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	mtx = (char**)malloc(sizeof(char*) * (i + 1));
	tmp = e;
	mtx[i] = NULL;
	while (tmp)
	{
		mtx[--i] = ft_strdup(tmp->content);
		tmp = tmp->next;
	}
	return (mtx);
}