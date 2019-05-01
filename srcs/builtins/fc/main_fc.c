/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/01 06:58:28 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	save_to_hist(t_fcparse *opt)
{
	int		i;

	if (!opt)
		return ;
	if (write(0, "c", 0) != -1)
	{
		i = ft_strlen(opt->shist);
		if (ft_strcmp(opt->shist, "\n") != 0 && i > 0 && opt->shist[0] > 32)
			lstcontainer_add(g_tracking.mysh->hist, ft_strdup(opt->shist));
	}
}

void	hist_set_unset(int i, t_fcparse *opt)
{
	t_list	*tmp;

	if (!g_tracking.mysh || !g_tracking.mysh->hist || !opt)
		return ;
	if (i == 0)
	{
		tmp = ft_lstgetlast(g_tracking.mysh->hist->lastelement);
		g_tracking.mysh->hist->lastelement = tmp->prev;
		opt->shist = ft_strdup(tmp->content);
		lstcontainer_remove(g_tracking.mysh->hist, tmp, 1);
		tmp = NULL;
	}
	if (i == 1)
	{
		if (!opt || opt->e == 1 || opt->s == 1)
			return ;
		else
			save_to_hist(opt);
	}
}

void	free_opt(t_fcparse *opt)
{
	if (!opt)
		return ;
	ft_strdel(&opt->editor);
	ft_strdel(&opt->first);
	ft_strdel(&opt->last);
	ft_strdel(&opt->shist);
	ft_strdel(&opt->str);
	ft_free(opt);
}

int		fc_builtin(void)
{
	char		**av;
	int			i;
	int			count;
	t_fcparse	*opt;

	av = g_tracking.g_tab_exec;
	g_tracking.fc++;
	opt = (fc_option(av, 1));
	i = 0;
	count = 0;
	hist_set_unset(0, opt);
	while (av[count])
		count++;
	if (opt->i > count || (opt = fc_offset(av, opt)) == NULL)
		return (1);
	if (opt->err != 0)
		fc_error(2, NULL);
	char_to_index(opt);
	fc_mode(opt);
	hist_set_unset(1, opt);
	free_opt(opt);
	return (0);
}
