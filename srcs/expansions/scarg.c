/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scarg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjose <mjose@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 01:03:07 by mjose             #+#    #+#             */
/*   Updated: 2019/03/25 06:08:44 by mjose            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void		expand_lstdel(t_expand *expan_head)
{
	t_expand	*element;
	t_expand	*next;

	if (expan_head == NULL)
		return ;
	element = expan_head;
	while ((void *)element != NULL)
	{
		next = element->next;
		ft_memdel((void *)&element);
		element = next;
	}
}

void		expan_arg(t_scan_arg *scarg)
{
	t_expand	*expan_head;

	if ((scarg->scan->sstring[0] != '~' && !scarg->checker->type)
			|| scarg->scan->sstring[0] == '$')
	{
		scarg->expand = new_expand(ft_strlen(scarg->scan->sstring));
		expan_head = scarg->expand;
		create_list_expand(scarg->expand, scarg->scan->sstring);
		transform(scarg->expand, &scarg->scan->sstring);
		expand_lstdel(expan_head);
	}
	else if (scarg->scan->sstring[0] == '~')
	{
		scarg->expand = new_expand(ft_strlen(scarg->scan->sstring));
		expan_head = scarg->expand;
		create_list_expand(scarg->expand, scarg->scan->sstring);
		transform_if_tilde(&scarg->expand, &scarg->scan->sstring);
		expand_lstdel(expan_head);
	}
	if (!scarg->new_arg)
		scarg->new_arg = ft_strnew(1);
	scarg->new_arg = ft_strjoinfree(scarg->new_arg, scarg->scan->sstring, 1);
	scarg->scan = scarg->scan->next;
//	expand_lstdel(expan_head);
	scarg->expand = NULL;
}

void		fill_scarg(t_scan_arg *scarg)
{
	t_scan		*scan_head;

	scarg->scan = new_scan();
	scan_head = scarg->scan;
	scarg->first_scan = scarg->scan;
	scan_argument(scarg->checker->str_unquoted, scarg->scan);
	scarg->new_arg = NULL;
	while (scarg->scan && scarg->scan->sstring)
		expan_arg(scarg);
	while (scarg->first_scan->sstring)
	{
		ft_strdel(&scarg->first_scan->sstring);
		ft_memdel((void **)scarg->first_scan);
		scarg->first_scan = scarg->first_scan->next;
	}
	if (scarg->new_arg)
	{
		ft_strdel(&scarg->checker->str_unquoted);
		scarg->checker->str_unquoted = scarg->new_arg;
	}
	scan_lstdel(scan_head);
}
