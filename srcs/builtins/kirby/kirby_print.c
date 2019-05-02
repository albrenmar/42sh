/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kirby_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 04:06:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/05/02 04:26:02 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		print_file(int i)
{
	char	*file;
	char	*str;
	int		fd;

	if (i == 1)
		file = "/tmp/kirby/sprite1v2.txt";
	if (i == 2)
		file = "/tmp/kirby/sprite2v2.txt";
	if (i == 3)
		file = "/tmp/kirby/sprite3v2.txt";
	if (i == 4)
		file = "/tmp/kirby/clash.txt";
	str = NULL;
	if ((fd = open(file, O_RDWR, 0644)) == -1)
		return (-5);
	while (get_next_line(fd, &str) > 0)
	{
		ft_putendl(str);
	}
	close(fd);
	return (0);
}

void	clear_box(void)
{
	char	*res;
	int		i;

	i = 8;
	while (i > 0)
	{
		tputs(tgetstr("up ", NULL), 1, yan_putchar);
		i--;
	}
	tputs(tgetstr("cr ", NULL), 1, yan_putchar);
	if ((res = tgetstr("cd", NULL)) == NULL)
		return ;
	tputs(res, 1, yan_putchar);
}

int		print_box(int i)
{
	char	*file;
	char	*str;
	int		fd;

	if (i == 0)
		file = "/tmp/kirby/Ready.txt";
	if (i == 1)
		file = "/tmp/kirby/P1wins.txt";
	if (i == 2)
		file = "/tmp/kirby/P2wins.txt";
	if (i == 3)
		file = "/tmp/kirby/GO.txt";
	if (i == 4)
		file = "/tmp/kirby/DUEL.txt";
	if (i == 5)
		file = "/tmp/kirby/DUEL2.txt";
	str = NULL;
	if (i == 3)
		clear_box();
	if ((fd = open(file, O_RDWR, 0644)) == -1)
		return (-5);
	while (get_next_line(fd, &str) > 0)
		ft_putendl(str);
	close(fd);
	return (0);
}

int		set_kirby_screen(void)
{
	char	*res;
	int		flag;

	flag = 0;
	if (g_tracking.terminfo->sizex < 60)
		flag++;
	if (g_tracking.terminfo->sizey < 80)
		flag++;
	if (flag != 0)
	{
		ft_putendl("Temsize too small");
		sleep(2);
		return (-2);
	}
	if ((res = tgetstr("cl", NULL)) == NULL)
		return (-2);
	tputs(res, 1, yan_putchar);
	return (0);
}

int		print_win(int i)
{
	if (i == 3)
	{
		print_stylish(2);
		i = 2;
		sleep(1);
	}
	if (i == 4)
	{
		print_stylish(1);
		i = 1;
		sleep(1);
	}
	if (set_kirby_screen() != 0)
		return (-1);
	print_file(i + 1);
	print_box(i);
	sleep(2);
	return (0);
}
