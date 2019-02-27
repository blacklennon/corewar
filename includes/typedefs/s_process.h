/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/27 16:33:59 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PROCESS_H
# define S_PROCESS_H

# include <stddef.h>
# include <stdint.h>
# include "op.h"

typedef struct			s_process
{
	char				*file_path;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	size_t				program_counter;
	uint8_t				carry;
	uint32_t			registers[REG_NUMBER];
	size_t				live_counter;
	size_t				next_op;
}						t_process;

typedef struct			s_vm
{
	uint8_t				memory[MEM_SIZE];
	size_t				nb_champs;
	struct s_process	process[MAX_PLAYERS];
	size_t				cycle;
	void				(*op_table[17])(t_process*, struct s_vm*);
}						t_vm;


#endif