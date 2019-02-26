/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_process.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:43:08 by pcarles           #+#    #+#             */
/*   Updated: 2019/02/26 20:03:46 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_PROCESS_H
# define S_PROCESS_H

# include <stdint.h>
# include "op.h"

typedef struct			s_process
{
	char				*file_path;
	char				name[PROG_NAME_LENGTH + 1];
	char				comment[COMMENT_LENGTH + 1];
	uint8_t				carry;
	uint32_t			program_counter;
	uint32_t			registers[REG_NUMBER];
}						t_process;

typedef struct			s_vm
{
	uint8_t				memory[MEM_SIZE];
	size_t				nb_champs;
	struct s_process	process[MAX_PLAYERS];
}						t_vm;


#endif