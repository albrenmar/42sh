/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_tilde.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:21:08 by mjose             #+#    #+#             */
/*   Updated: 2019/03/05 22:00:35 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int		scan_other(char *arg, char **new_arg)
{
	int		i;
	char	*fill_arg;

	i = 0;
	fill_arg = *new_arg;
	while (arg[i] && arg[i] != '$')
	{
		fill_arg[i] = arg[i];
		i++;
	}
	return (i);
}

int		scan_dollar_key(char *arg, char **new_arg)
{
	int		i;
	char	*fill_arg;

	i = 1;
	fill_arg = *new_arg;
	while (arg[i] && arg[i] != '}')
	{
		fill_arg[i] = arg[i];
		i++;
	}
	fill_arg[i] = arg[i];
	return (++i);
}

int		scan_dollar(char *arg, char **new_arg)
{
	int		i;
	char	*fill_arg;

	i = 1;
	fill_arg = *new_arg;
	fill_arg[0] = arg[0];
	if (arg[i] && arg[i] == '{')
	{
		return (scan_dollar_key(arg, &fill_arg));
/*		while (arg[i] && arg[i] != '}')
		{
			fill_arg[i] = arg[i];
			i++;
		}
		if (arg[i])
			return (++i);
		return (i);
*/	}
	while (arg && arg[i])
	{
		if (arg[i] == '/' || arg[i] == '~')
			return (i);
		else if (arg[i] == '$' || ft_iswhitespace(arg[i]))
			return (i);
		fill_arg[i] = arg[i];
		i++;
	}
	return (i);
}

int		scan_tilde(char *arg, char **new_arg)
{
	int		i;
	char	*fill_arg;

	i = 0;
	fill_arg = *new_arg;
	while (arg && arg[i])
	{
		if (arg[i] == '/')
		{
			fill_arg[i] = arg[i];
			return (++i);
		}
		else if (arg[i] == '$' || ft_iswhitespace(arg[i]))
			return (--i);
		fill_arg[i] = arg[i];
		i++;
	}
	return (i);
}
