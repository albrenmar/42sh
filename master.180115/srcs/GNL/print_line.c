/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/13 21:10:57 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/sh42.h"

void	print_line(void)
{
	int		a;
	int		i;
	char	*end;
	char	*str;

	if (g_tracking.str != NULL)
	{
		clear_screen3();
		ft_dprintf(2, "%s", g_tracking.prompt);
		ft_putstr_nocar(g_tracking.str);
	}
}

void		print_line_cpy(void)
{
	int		start;
	int		end;
	int		i;

	start = g_tracking.cpaste->b1;
	end = g_tracking.cpaste->b2;
	i = 0;
	if (end < start)
	{
		start = g_tracking.cpaste->b2;
		end = g_tracking.cpaste->b1;
	}
	start = utf_goto(g_tracking.str, start);
	end = utf_goto(g_tracking.str, end);
	clear_screen3();
	ft_dprintf(2, "%s", g_tracking.prompt);
	while (g_tracking.str[i])
	{
		if (i == start)
			ft_putstr("\033[7m");
		if (i == end)
			ft_putstr("\033[0m");
		ft_putchar(g_tracking.str[i]);
		i++;
	}
	ft_putstr("\033[0m");
	back_to_pos();
}