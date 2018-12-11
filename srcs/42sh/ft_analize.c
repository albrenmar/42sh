/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 14:39:15 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/05 16:00:56 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_last	*create_new_list(void)
{
	t_last	*list;

	list = malloc(sizeof(t_last));
	list->name = NULL;
	list->next = NULL;
	return (list);
}

char	*recup_cmd(char *line, int *i, int nb)
{
	char	*test;
	int		gui;
	int		par;

	gui = 0;
	par = 0;
	test = NULL;
	while (line[nb])
	{
		if (line[nb] == ';' && par == 0 && gui == 0)
		{
			nb++;
			test = ft_strndup(line, nb - 1);
			(*i) = nb + *i;
			return (test);
		}
		else if (line[nb] == '&' && line[nb + 1] == '&')
		{
			nb = nb + 2;
			test = ft_strndup(line, nb - 2);
			(*i) = nb + *i;
			return (test);
		}
		else if (line[nb] == ';' && par == 1 && gui == 0)
		{
			printf("Parenthese non ferme");
			exit(0);
		}
		if (PO && par >= 0)
			par++;
		if (PF && par > 0)
			par--;
		else if (PF && par == 0)
		{
			printf("Mauvaise parenthese fermante\n");
			exit(0);
		}
		if (GO && gui >= 0)
		{
			if (gui % 2 == 0)
				gui++;
			else
				gui--;
		}
		nb++;
	}
	if (gui > 0)
	{
		printf("Erreur de guillemets");
		exit(0);
	}
	if (par > 0)
	{
		printf("Parenthese non ferme");
		exit(0);
	}
	if (nb > 0)
	{
		test = ft_strndup(line, nb);
		*i = nb + *i;
		return (test);
	}
	else
		return (NULL);
}

t_cmd	*ft_analize(char *line)
{
	char	*temp;
	int		i;
	int		j;
	t_cmd	*cmd;
	t_last	*templist;

	i = 0;
	j = 0;
	cmd = ft_memalloc(sizeof(t_cmd));
	cmd->beginlist = create_new_list();
	templist = cmd->beginlist;
	while ((temp = recup_cmd(&line[i], &i, 0)) != NULL)
	{
		templist->name = ft_strdup(temp);
		free(temp);
		templist->next = ft_memalloc(sizeof(t_last));
		templist = templist->next;
	}
	templist = cmd->beginlist;
	return (cmd);
}