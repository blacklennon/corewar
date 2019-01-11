/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:51:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/11 19:16:24 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "label.h"

void		create_label(char *name, int index, t_label **label_listp)
{
	t_label	*new;
	t_label	*tmp;

	if (!name || !label_listp || !(new = (t_label*)malloc(sizeof(*new))))
		return ;
	new->name = name;
	new->index = index;
	new->next = NULL;
	if (!(*label_listp))
		*label_listp = new;
	tmp = *label_listp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_label		*find_label(char *name, t_label *label_list)
{
	while (label_list)
	{
		if (!ft_strcmp(name, label_list->name))
			return (label_list);
		label_list = label_list->next;
	}
	return (NULL);
}