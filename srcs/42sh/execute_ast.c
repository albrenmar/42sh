/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by alsomvil          #+#    #+#             */
/*   Updated: 2019/02/19 06:14:20 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/sh42.h"

t_order		*new_order(void)
{
	t_order		*order;

	order = ft_memalloc(sizeof(t_order));
	order->command = NULL;
	order->next = NULL;
	order->prev = NULL;
	order->temp_command = NULL;
	return (order);
}

char		**copy_tab(char **copy)
{
	int		i;
	int		j;
	char	**tabcpy;

	i = 0;
	j = 0;
	while (copy[i])
		i++;
	tabcpy = ft_memalloc(sizeof(char *) * (i + 1));
	tabcpy[i] = NULL;
	i = 0;
	while (copy[i])
	{
		tabcpy[i] = ft_strdup(copy[i]);
		i++;
	}
	tabcpy[i] = NULL;
	return (tabcpy);
}

void		add_to_exec(int mode)
{
	if (ORDER)
	{
		while (ORDER->next)
		{
			ORDER = ORDER->next;
		}
		ORDER->next = new_order();
		ORDER->next->prev = ORDER;
		ORDER = ORDER->next;
	}
	else
		ORDER = new_order();
	ORDER->command = copy_tab(EXEC->left);
	if (EXEC->sym && mode == 0)
		ORDER->sym = ft_strdup(EXEC->sym[0]);
	else
		ORDER->sym = NULL;
}

void		exec_command(t_jobs *job)
{
	int		status;
	t_order		*temp_command;
	t_order		*temp_command_next;
	pid_t	gpid;
	pipe(descrf);
	pipe(descrf_two);
	int		j;
	int		close_fd;

	j = 0;
	EXEC->pid_exec = 0;
	EXEC->gpid = 0;
	EXEC->ret = 0;
	while (ORDER->prev)
		ORDER = ORDER->prev;
	if (!ORDER->next)
	{
		execute_pipe_two(job, 0);
		ORDER = ORDER->next;
	}
	while (ORDER)
	{
		while (ORDER && ORDER->sym && ORDER->sym[0] == '|')
		{
			descrf[0] = descrf_two[0];
			descrf[1] = descrf_two[1];
			pipe(descrf_two);
			execute_pipe(job);
			ORDER = ORDER->next;
			if (!ORDER->next)
			{
				execute_pipe_two(job, 0);
				ORDER = ORDER->next;
			}
		}
		if (ORDER && ORDER->sym && ORDER->sym[0] == '>')
		{
			temp_command = ORDER;
			while (ORDER && ORDER->sym && ORDER->sym[0] == '>')
			{
				ORDER = ORDER->next;
				if (ft_strlen(ORDER->sym) == 1)
					close_fd = open(ORDER->command[0], O_CREAT | O_TRUNC | O_RDWR, 0644);
				else
					close_fd = open(ORDER->command[0], O_CREAT | O_APPEND | O_RDWR, 0644);
			}
			ORDER = ORDER->next;
			temp_command_next = ORDER;
			ORDER = temp_command;
			execute_pipe_two(job, close_fd);
			close(close_fd);
			ORDER = temp_command_next;
		}
	}
	if (EXEC->ret == 0)
		EXEC->ret = 1;
}

void		execute_ast(t_tree *tree, t_tab_arg *tab_arg, t_jobs *job)
{
	if (tree->left)
		execute_ast(tree->left, tab_arg, job);
	if (tree->type == OP)
		EXEC->sym = tree->cmd;
	if ((!EXEC->left || !EXEC->right) && !tree->left)
	{
		if (!EXEC->left)
			EXEC->left = tree->cmd;
		else
			EXEC->right = tree->cmd;
	}
	if (EXEC->left && EXEC->right)
	{
		if (((ft_strlen(EXEC->sym[0]) == 2) && ((EXEC->sym[0][0] == '|') || EXEC->sym[0][0] == '&')) || EXEC->sym[0][0] == ';')
		{
			add_to_exec(1);
			if (EXEC->ret == 0)
				exec_command(job);
			if ((EXEC->ret == 1 && (EXEC->sym[0][0] == '&' || EXEC->sym[0][0] == ';')) || (EXEC->ret == -1 && EXEC->sym[0][0] == '|'))
				EXEC->ret = 0;
			ORDER = NULL;
		}
		else
			add_to_exec(0);
		EXEC->left = EXEC->right;
		EXEC->right = NULL;
		return ;
	}
	if (tree->type == OP &&
			(ft_strlen(tree->name) != 2 || (tree->name[0] != '|' && tree->name[0] != '&')))
		EXEC->sym = tree->cmd;
	if (tree->right)
		execute_ast(tree->right, tab_arg, job);
	return ;
}