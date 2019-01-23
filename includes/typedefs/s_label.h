/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_label.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:44:39 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/23 14:46:35 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_LABEL_H
# define S_LABEL_H

# include <stddef.h>

typedef struct		s_label
{
	char					*name;
	size_t					index;
	struct s_instruction	*instruction;
	struct s_label			*next;
}					t_label;

#endif