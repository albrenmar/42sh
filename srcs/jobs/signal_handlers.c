/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abe <abe@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/15 12:52:33 by alsomvil          #+#    #+#             */
/*   Updated: 2019/03/07 07:05:44 by abe              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "sh42.h"

void		sig_int_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar('\n');
		signal(SIGINT, sig_int_handler);
	}
}

void		sig_winch_handler(int signo)
{
	int			i;
	int			y;

	if (signo == SIGWINCH)
	{
		get_size();
		update_pos();
		y = utf_strlen(g_tracking.str);
		y += g_tracking.pos->prompt;
		g_tracking.pos->y = y / g_tracking.terminfo->sizex;
		if (g_tracking.aut)
			ioctl(STDERR_FILENO, TIOCSTI, "'");
		signal(SIGWINCH, sig_winch_handler);
	}
}

void		set_process_signal_handlers(void)
{
	// struct sigaction signalAction;
    // signalAction.sa_handler = SIG_DFL;
    // sigemptyset(&signalAction.sa_mask);
    // signalAction.sa_flags = 0;      // SA_RESTART;
    // sigaction(SIGTSTP, &signalAction, NULL);

	// // struct sigaction signalAction;
    // signalAction.sa_handler = SIG_DFL;
    // sigemptyset(&signalAction.sa_mask);
    // signalAction.sa_flags = 0;      // SA_RESTART;
    // sigaction(SIGSTOP, &signalAction, NULL);


	// // struct sigaction signalAction;
    // signalAction.sa_handler = SIG_DFL;
    // sigemptyset(&signalAction.sa_mask);
    // signalAction.sa_flags = 0;      // SA_RESTART;
    // sigaction(SIGCONT, &signalAction, NULL);

	// signal(SIGKILL, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGCONT, SIG_DFL);
	// signal(SIGSTOP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
}

void		set_shell_signal_handlers(void)
{
	// signal(SIGSEGV, SIG_IGN);
	// signal(SIGKILL, SIG_IGN);
	// signal(SIGABRT, SIG_IGN);

	signal(SIGINT, sig_int_handler);
	signal(SIGWINCH, sig_winch_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
	// signal(SIGSTOP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_DFL);
	// signal(SIGCHLD, SIG_IGN);
}

// void					set_process_signal_handlers(void)
// {
// 	// signal(SIGSEGV, SIG_IGN);
// 	// signal(SIGABRT, SIG_IGN);
// 	// signal(SIGKILL, SIG_DFL);
// 	// signal(SIGSTOP, SIG_DFL);
// 	struct sigaction	psa;
    
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGINT, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGQUIT, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGTSTP, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGCONT, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGTTIN, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGTTOU, &psa, NULL);
// 	psa.sa_handler = SIG_DFL;
//     sigaction(SIGCHLD, &psa, NULL);

// 	// signal(SIGINT, SIG_DFL);
// 	// signal(SIGQUIT, SIG_DFL);
// 	// signal(SIGTSTP, SIG_DFL);
// 	// signal(SIGCONT, SIG_DFL);
// 	// signal(SIGTTOU, SIG_DFL);
// 	// signal(SIGTTIN, SIG_DFL);
// 	// signal(SIGCHLD, SIG_DFL);
// }

// void					set_shell_signal_handlers(void)
// {
// 	// signal(SIGSEGV, SIG_IGN);
// 	// signal(SIGABRT, SIG_IGN);
// 	// signal(SIGKILL, SIG_IGN);
// 	// signal(SIGSTOP, SIG_IGN);
// 	struct sigaction	psa;

//     psa.sa_handler = sig_int_handler;
//     sigaction(SIGINT, &psa, NULL);
// 	psa.sa_handler = sig_winch_handler;
//     sigaction(SIGWINCH, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGQUIT, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGTSTP, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGCONT, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGTTIN, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGTTOU, &psa, NULL);
// 	psa.sa_handler = SIG_IGN;
//     sigaction(SIGCHLD, &psa, NULL);

// 	// signal(SIGWINCH, sig_winch_handler);
// 	// signal(SIGINT, sig_int_handler);
// 	// signal(SIGQUIT, SIG_IGN);
// 	// signal(SIGTSTP, SIG_IGN);
// 	// signal(SIGCONT, SIG_IGN);
// 	// signal(SIGTTOU, SIG_IGN);
// 	// signal(SIGTTIN, SIG_IGN);
// 	// signal(SIGCHLD, SIG_IGN);
// }