/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:10:01 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/03 16:47:40 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# define ERROR_IS_NOT_A_POSITIVE_INTEGER -1
# define ERROR_IS_NOT_A_VALID_NUMBER -2
# define ERROR_IS_NOT_A_VALID_VERBOSE_INT -3
# define ERROR_IS_NOT_A_VALID_OPTION -4

# include <stddef.h>
# include "op.h"
# include "libft.h"
# include "ft_printf.h"

int			main(int ac, char **av);
void		init_vm(t_vm *vm);
void		mem_dump(uint8_t *p, size_t size, size_t octet_highlight);
void		reg_dump(t_process *process);
void		load_champs(t_vm *vm);
void		launch(t_vm *vm);
void		crash(t_process *process, char *str);
t_vm		*get_vm(t_vm *new_vm);
void		free_process(t_process *process_list);
int			check_is_alive(t_vm *vm);

void		get_value_of_arg(t_process *process, t_int_types *value, \
			t_int_types_enum *type, int opcode);
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
void		op_fork(t_process *process, t_args *args);
void		op_lld(t_process *process, t_args *args);
void		op_lldi(t_process *process, t_args *args);
void		op_lfork(t_process *process, t_args *args);
void		op_aff(t_process *process, t_args *args);

int32_t		read4_memory(t_vm *vm, size_t index);
int16_t		read2_memory(t_vm *vm, size_t index);
int8_t		read1_memory(t_vm *vm, size_t index);
void		write4_memory(t_vm *vm, int32_t value, size_t index);
void		write2_memory(t_vm *vm, int16_t value, size_t index);

/*
**	Options
*/

void		parse_arguments(int ac, char **av, t_vm *vm);

#endif
