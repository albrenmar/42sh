/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_fc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 04:44:37 by bsiche            #+#    #+#             */
/*   Updated: 2019/04/21 04:45:39 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		fc_builtin(void)
{
	char	*av;
	int		rev;
	char	*option;

	av = g_tracking.g_tab_exec;
	option = (fc_option(av));
}