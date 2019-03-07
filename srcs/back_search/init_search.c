/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 22:04:28 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 04:17:40 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/02/26 03:30:20 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

<<<<<<< HEAD
void		back_up(void)
=======
void	back_up(void)
>>>>>>> alsomvil
{
	int		y;
	int		i;
	int		winx;

	winx = g_tracking.terminfo->sizex;
	if (g_tracking.found)
		i = utf_strlen(g_tracking.found);
	else
		i = ft_strlen("No such string in history");
	i = i + ft_strlen("(back-i-search) :_ ::");
	i = i + ft_strlen(g_tracking.search);
	y = i / winx;
	y++;
	if (i % winx == 0)
		y--;
	tputs(tgetstr("cr", NULL), 1, yan_putchar);
	while (y != 0)
	{
		y--;
		tputs(tgetstr("up", NULL), 1, yan_putchar);
	}
}

<<<<<<< HEAD
int			ft_return_key(void)
{
	if (g_tracking.found)
	{
		ft_bzero(g_tracking.str, g_tracking.buffsize);
		g_tracking.pos->abs = 0;
		add_to_str(ft_strdup(g_tracking.found));
	}
	else
	{
		print_line();
		back_to_pos();
	}
	g_tracking.found = NULL;
	g_tracking.search = NULL;
	return (1);
}

int			read_search(void)
=======

int		read_search()
>>>>>>> alsomvil
{
	char	c;

	c = 0;
	read(STDERR_FILENO, &c, 1);
	if (c == 10)
<<<<<<< HEAD
		return (ft_return_key());
	if (c == 18)
	{
		if (g_tracking.histindex > 1)
			g_tracking.histindex--;
=======
	{
		if (g_tracking.found)
		{
			ft_bzero(g_tracking.str, g_tracking.buffsize);
			g_tracking.pos->abs = 0;
			add_to_str(ft_strdup(g_tracking.found));
		}
		else
		{
			print_line();
			back_to_pos();
		}
		g_tracking.found = NULL;
		g_tracking.search = NULL;
		return (1);
	}
	if (c == 18)
	{
        if (g_tracking.histindex > 1)
		   	g_tracking.histindex--;
>>>>>>> alsomvil
	}
	if (c == 127)
	{
		if (ft_strlen(g_tracking.search) > 0)
		{
			g_tracking.search = ft_strsub(g_tracking.search, 0,
			(ft_strlen(g_tracking.search) - 1), 1);
		}
		return (0);
	}
	if (c < 32)
		return (2);
	tputs(tgetstr("le", NULL), 1, yan_putchar);
	g_tracking.search = ft_strjoinchar(g_tracking.search, c, 1);
	return (0);
}

<<<<<<< HEAD
int			begin_search(void)
=======
int		begin_search(void)
>>>>>>> alsomvil
{
	int		y;

	g_tracking.search = ft_strnew(0);
	y = 0;
	tputs(tgetstr("do", NULL), 1, yan_putchar);
	ft_putstr("(back-i-search) :");
	tputs(tgetstr("up", NULL), 1, yan_putchar);
	while (read_search() != 1)
	{
		tputs(tgetstr("do", NULL), 1, yan_putchar);
		tputs(tgetstr("cd", NULL), 1, yan_putchar);
		ft_putstr("(back-i-search) :");
		ft_putstr(g_tracking.search);
		ft_putstr("_ ::");
		g_tracking.found = get_hist_ptr(g_tracking.search);
		if (!g_tracking.found)
			ft_putstr("No such string in history");
		else
			ft_putstr(g_tracking.found);
		get_hist_ptr(g_tracking.search);
		back_up();
	}
	free(g_tracking.search);
	g_tracking.search = NULL;
	return (0);
}
