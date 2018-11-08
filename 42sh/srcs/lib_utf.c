/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 15:24:45 by bsiche            #+#    #+#             */
/*   Updated: 2018/10/30 15:31:08 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int			utf_byte(char c)
{
	if ((c & 0xC0) != 0x80)
		return (0);
	return (1);
}

int			utf_strlen(char *str)
{
	int i;
	int a;

	i = 0;
	a = 0;
	while (str[i])
	{
		if ((str[i] & 0xC0) != 0x80)
			a++;
		i++;
	}
	return (a);
}
