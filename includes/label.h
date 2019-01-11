/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:48:07 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/11 19:16:55 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LABEL_H
# define LABEL_H

typedef struct		s_label
{
	char			*name;
	int				index;
	struct s_label	*next;
}					t_label;

void				create_label(char *name, int index, t_label **label_listp);
t_label				*find_label(char *name, t_label *label_list);

#endif