/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 07:59:43 by mjose             #+#    #+#             */
/*   Updated: 2019/03/02 05:19:41 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	exec_echo(void)
{
	char	**tab_arg;

	tab_arg = g_tracking.g_tab_exec + 1;
	while (*tab_arg)
	{
		ft_putstr(*tab_arg);
		ft_putchar(' ');
		tab_arg++;
	}
	ft_putchar('\n');
}

int		check_and_exec_echo(void)
{
	char	**tab_arg;

	tab_arg = g_tracking.g_tab_exec + 1;
	if (!tab_arg)
		ft_putchar('\n');
	else
		exec_echo();
	return (0);
}