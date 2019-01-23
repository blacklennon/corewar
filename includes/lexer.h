/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:38:18 by pcarles           #+#    #+#             */
/*   Updated: 2019/01/23 14:42:48 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "parser.h"

typedef struct		s_lexer
{
	t_label			*last_label;
}					t_lexer;

#endif