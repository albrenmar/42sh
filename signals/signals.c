/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 22:19:20 by mjose             #+#    #+#             */
/*   Updated: 2018/11/23 02:28:28 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell/includes/minishell.h"

int		flag = 1;
int		pid;
int		status;

void	kill_child(int signum)
{
	ft_putendl("Has apretado CTRL+C mato proceso hijo");
	ft_putnbr(signum);
	ft_putchar('\n');
	kill(pid, SIGINT);
}

void	stop_child(int signum)
{
	ft_putendl("Has apretado CTRL+Z paro proceso hijo");
	ft_putnbr(signum);
	ft_putchar('\n');
	kill(pid, SIGSTOP);
	while(1);
	printf("pud = %d\n", pid);
	kill(getpid(), SIGUSR1);
}

void	rec_z(int signum)
{
	// kill(getppid(), SIGUSR1);
	// ft_putendl("Recibo CTRL+Z del padre");
	// ft_putnbr(signum);
	// ft_putchar('\n');
	while (signum);
}

int		main(void)
{
	char	*line;

	line = NULL;
	printf("P1 = %d\n", getpid());
	signal(SIGTSTP, SIG_IGN);
	if (fork() == 0)
	{
		printf("P2 = %d\n", getpid());
		ft_putendl("Presiona CTRL+C o CTRL+Z:");
		if ((pid = fork()) == 0)
		{
			printf("P3 = %d\n", getpid());
			while (flag);
			// 	if (signal(WSTOPPED, &rec_z))
			// 	{
			// 		flag = 0;
			// 	}
			// while (!flag);
		}
		else
		{
			signal(SIGINT, &kill_child);
			signal(SIGTSTP, &stop_child);
			waitpid(pid, &status, WUNTRACED);
			printf("status = %d\n", status);
			if (status == 2)
			{
				ft_putendl("Hemos matado el hijo");
				exit(0);
			}
			else if (WIFSTOPPED(status))
			{
				while (1);
				signal(SIGUSR1, &rec_z);
				ft_putendl("Hemos parado el hijo hay que matarlo a mano");
				ft_putnbr(pid);
				exit(0);
			}
		}
	}
	else
	{
		wait(&status);
		exit(0);
	}
	return (0);
}