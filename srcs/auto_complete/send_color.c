/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 05:04:47 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 01:41:45 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/01/13 22:33:19 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*send_color(int i)
{
<<<<<<< HEAD
=======
	if (i == 0)
		return (NULL);
>>>>>>> alsomvil
	if (i == 1)
		return ("\033[30;42m");
	if (i == 2)
		return ("\033[43m");
	if (i == 3)
		return ("\033[36;1m");
	if (i == 4)
		return ("\033[30;41m");
	if (i == 5)
		return ("\033[30;46m");
	if (i == 6)
		return ("\033[31m");
	if (i == 7)
		return ("\033[33m");
	if (i == 8)
		return ("\033[35m");
	if (i == 9)
		return ("\033[34;46m");
	if (i == 10)
		return ("\033[34;43m");
	if (i == 11)
		return ("\033[32m");
	if (i == 12)
		return ("\033[0m");
	return (NULL);
}
<<<<<<< HEAD
=======

>>>>>>> alsomvil
