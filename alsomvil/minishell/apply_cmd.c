/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:52:15 by alsomvil          #+#    #+#             */
/*   Updated: 2018/12/05 05:14:58 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	create_tab_path(t_tab *st_tab, char **env)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (env[++i])
	{
		str = ft_strndup(env[i], 5);
		if (ft_strcmp(str, "PATH=") == 0)
		{
			free(str);
			st_tab->tab_path = ft_strsplit(&env[i][5], ':');
			while (st_tab->tab_path[j])
			{
				str = ft_strjoin(st_tab->tab_path[j], "/");
				free(st_tab->tab_path[j]);
				st_tab->tab_path[j++] = str;
			}
			return ;
		}
		else
			free(str);
	}
	st_tab->tab_path = NULL;
}

void	recup_argument(t_tab *st_tab, t_env *st_env, char **line)
{
	if (*line && ft_strcmp(*line, "") != 0)
		st_tab->tab_word = ft_strsplit(*line, ' ');
	if (ft_strcmp(*line, "exit") == 0)
	{
		forfree(st_tab->tab_word);
		free(*line);
		exit(0);
	}
}

int		test_exist_fonction_two(t_tab *st_tab, t_env *st_env,
		pid_t father, char *next_str)
{
	int		i;

	i = 0;
	while (st_tab->tab_path && st_tab->tab_path[i])
	{
		next_str = ft_strjoin(st_tab->tab_path[i], st_tab->tab_word[0]);
		if (access(next_str, X_OK) == 0)
		{
			father = fork();
			if (father == 0)
				execve(next_str, st_tab->tab_word, st_env->env);
			free(next_str);
			wait(&father);
			forfree(st_tab->tab_path);
			return (1);
		}
		else
		{
			free(next_str);
			i++;
		}
	}
	return (0);
}

void	test_exist_fonction(t_tab *st_tab, char **line, t_env *st_env)
{
	char	*next_str;
	int		i;
	int		test_proc;
	pid_t	father;

	i = 0;
	if (access(st_tab->tab_word[0], X_OK) == 0)
	{
		father = fork();
		if (father == 0)
			execve(st_tab->tab_word[0], st_tab->tab_word, st_env->env);
		wait(&father);
		return ;
	}
	else
	{
		create_tab_path(st_tab, st_env->env);
		if (test_exist_fonction_two(st_tab, st_env, father, next_str) == 1)
			return ;
		forfree(st_tab->tab_path);
	}
	ft_dprintf(2, "%s%s\n", "42sh: command not found: ",
			st_tab->tab_word[0]);
	return ;
}

void	apply_builtin(t_tab *st_tab, t_env *st_env, char *cmd, char **env)
{
	if (ft_strcmp(cmd, "") != 0 && verif_char(cmd) == 1)
	{
		recup_argument(st_tab, st_env, &cmd);
		if (!check_is_builtins(st_tab))
			test_exist_fonction(st_tab, &cmd, st_env);
		else if (check_is_builtins(st_tab))
			realize_built(st_tab, st_env, &cmd, env);
		forfree(st_tab->tab_word);
	}
}
void	test_exist_fonction_pipe(t_tab *st_tab, t_tab *st_tab2 , char **line1, char **line2, t_env *st_env)
{
	char	*next_str;
	int		i;
	int		test_proc;
	pid_t	father;
	int		descrf[2];

	i = 0;
	if (access(st_tab->tab_word[0], X_OK) == 0 && access(st_tab2->tab_word[0], X_OK) == 0)
	{
		pipe(descrf);
		father = fork();
		if (father == 0)
		{
			close(descrf[READ]);
			dup2(descrf[WRITE], 1);
			close(descrf[WRITE]);
			execve(st_tab->tab_word[0], st_tab->tab_word, st_env->env);
		}
		else
		{
			close(descrf[WRITE]);
			dup2(descrf[READ], 0);
			close(descrf[READ]);
			execve(st_tab2->tab_word[0], st_tab2->tab_word, st_env->env);
		}
		wait(&father);
		return ;
	}
	else
	{
		create_tab_path(st_tab, st_env->env);
		if (test_exist_fonction_two(st_tab, st_env, father, next_str) == 1)
			return ;
		forfree(st_tab->tab_path);
	}
	ft_dprintf(2, "%s%s\n", "42sh: command not found: ",
			st_tab->tab_word[0]);
	return ;
}

void	apply_builtin_tree(t_tab *st_tab, t_env *st_env, t_tree *tree, char **env)
{
	t_tab	st_tab2;
	char	*cmd1;
	char	*cmd2;

	cmd1 = tree->str1;
	cmd2 = tree->str2;
	if (ft_strcmp(cmd1, "") != 0 && verif_char(cmd1) == 1)
	{
		if (ft_strcmp(cmd2, "") != 0 && verif_char(cmd2) == 1)
		{
			recup_argument(st_tab, st_env, &cmd1);
			recup_argument(&st_tab2, st_env, &cmd2);
		}
		if (!check_is_builtins(st_tab) && (!check_is_builtins(&st_tab2)))
			test_exist_fonction_pipe(st_tab, &st_tab2, &cmd1, &cmd2, st_env);
		else if (check_is_builtins(st_tab))
			realize_built(st_tab, st_env, &cmd1, env);
		forfree(st_tab->tab_word);
	}
}
