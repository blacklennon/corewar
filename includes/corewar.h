/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:10:01 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/13 23:01:28 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "typedefs/s_process.h"

int			main(int ac, char **av);
void		init_vm(t_vm *vm);
void		mem_dump(uint8_t *p, size_t size);
void		reg_dump(t_vm *vm);
void		load_champs(t_vm *vm);
int32_t		swap_int32(int32_t value);
int16_t 	swap_int16(int16_t value);
void		launch(t_vm *vm);
void		crash(t_process *process, char *str);
t_vm		*get_vm(t_vm *new_vm);

//jac 12032019

void		op_live(t_process *process, t_args *args);
void		op_ld(t_process *process, t_args *args);
void		op_st(t_process *process, t_args *args);
void		op_add(t_process *process, t_args *args);
void		op_sub(t_process *process, t_args *args);
void		op_and(t_process *process, t_args *args);
void		op_or(t_process *process, t_args *args);
void		op_xor(t_process *process, t_args *args);
void		op_zjmp(t_process *process, t_args *args);
void		op_ldi(t_process *process, t_args *args);
void		op_sti(t_process *process, t_args *args);
//void		op_fork(t_process *process, t_args *args);
//void		op_lld(t_process *process, t_args *args);
//void		op_lldi(t_process *process, t_args *args);
//void		op_lfork(t_process *process, t_args *args);
void		op_aff(t_process *process, t_args *args);

int32_t		read4_memory(t_vm *vm, size_t index);
int16_t		read2_memory(t_vm *vm, size_t index);
int8_t		read1_memory(t_vm *vm, size_t index);
void		write4_memory(t_vm *vm, int32_t value, size_t index);
void		write2_memory(t_vm *vm, int16_t value, size_t index); //jac 12032019

#endif