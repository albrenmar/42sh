/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 05:23:25 by bsiche            #+#    #+#             */
/*   Updated: 2019/01/18 04:25:12 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	check_term(char *name)
{
	int			a;
	char		buf[1024];

	if (isatty(0) != 1)
	{
		ft_putendl("Not a terminal");
		exit(0);
	}
	a = tgetent(buf, name);
	if (a == 0)
		ft_putendl("No such entry in terminal database");
	if (a == -1)
		ft_putendl("Terminfo database could not be found");
	if (a != 1)
		exit(0);
}

int		clear_screen3(void)
{
	char	*res;
	char	*test;

	back_home();
	if ((res = tgetstr("cd", NULL)) == NULL)
		return (-1);
	tputs(res, 1, yan_putchar);
	return (0);
}

int		clear_screen2(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-1);
	tputs(res, 1, yan_putchar);
	return (0);
}

void	get_term(void)
{
	char			*name_term;
	struct termios	term;

	if (!(name_term = getenv("TERM")))
	{
		ft_putendl("No terminal found in ENV");
		exit(0);
	}
	check_term(name_term);
	tcgetattr(0, &term);
	tcgetattr(0, &g_tracking.default_term);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &term);
	g_tracking.terminfo = malloc(sizeof(t_term_data*));
	g_tracking.myterm = term;
	get_size();
}