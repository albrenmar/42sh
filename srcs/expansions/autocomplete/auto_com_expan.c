/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_com_expan.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 03:46:47 by mjose             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/04 14:09:25 by mjose            ###   ########.fr       */
=======
/*   Updated: 2019/02/28 04:06:45 by mjose            ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char	*ft_exp_complete(char *arg)
{
	char	*tmp;

	if (arg)
	{
		tmp = ft_strdup(arg);
<<<<<<< HEAD
		expand_transformer(&tmp, 0);
=======
		expand_transformer(&tmp);
>>>>>>> alsomvil
		return (tmp);
	}
	return (NULL);
}
