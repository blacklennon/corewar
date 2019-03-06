/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:10:01 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/06 15:45:45 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "typedefs/s_process.h"

int			main(int ac, char **av);
void		init_vm(t_vm *vm);
void		mem_dump(uint8_t *p, size_t size);
void		load_champs(t_vm *vm);
int32_t		swap_int32(int32_t value);
int16_t 	swap_int16(int16_t value);
void		launch(t_vm *vm);

void		live(t_process *process, t_vm *vm);
void		zjmp(t_process *process, t_vm *vm);
void		aff(t_process *process, t_vm *vm);

int32_t		read4_memory(t_vm *vm, size_t index);
int16_t		read2_memory(t_vm *vm, size_t index);
void		write4_memory(t_vm *vm, int32_t value, size_t index);

#endif