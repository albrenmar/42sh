/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 22:58:59 by bsiche            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/03/06 00:58:53 by bsiche           ###   ########.fr       */
=======
/*   Updated: 2019/01/20 06:18:41 by bsiche           ###   ########.fr       */
>>>>>>> alsomvil
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_lstcontainer		*type_ls(int argc, char **argv)
{
	int				i;
	char			*str;
	int				flag;
	int				called;
	t_lstcontainer	*liste;

	i = 1;
	flag = 0;
	called = 0;
	str = ft_strdup("-ld");
	if (argc == 1)
	{
		liste = ft_ls(".", str, 0);
		free(str);
		return (liste);
	}
	i = ft_option(argv, &str, &flag);
	while (argc > i && flag != 1)
	{
		liste = ft_ls(argv[i], str, called);
		i++;
		called = 1;
	}
	free(str);
	return (liste);
}

<<<<<<< HEAD
char				*get_option(void)
{
	char			*str;
	if (g_tracking.aut->hidden == 0)
		str = ft_strdup("-G");
	else
		str = ft_strdup("-aG");
	return (str);
}

=======
>>>>>>> alsomvil
t_lstcontainer		*modified_ls(int argc, char **argv)
{
	int				i;
	char			*str;
	int				flag;
	int				called;
	t_lstcontainer	*liste;

	i = 1;
	flag = 0;
	called = 0;
<<<<<<< HEAD
	str = get_option();
=======
	str = ft_strdup("-G");
>>>>>>> alsomvil
	if (argc == 1)
	{
		liste = ft_ls(".", str, 0);
		free(str);
		return (liste);
	}
	i = ft_option(argv, &str, &flag);
	while (argc > i && flag != 1)
	{
		liste = ft_ls(argv[i], str, called);
		i++;
		called = 1;
	}
	free(str);
	return (liste);
}
