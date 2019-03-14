/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdufer <hdufer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:26:47 by bsiche            #+#    #+#             */
/*   Updated: 2019/03/14 17:56:15 by hdufer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		print_hist()
{
	t_hist		*history;

	history = g_tracking.mysh->hist;
	if (!history)
		return (1);
	while (history)
	{
		ft_putendl(history->line);
		history = history->next;
	}
	return (0);
}