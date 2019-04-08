/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:42:16 by pcarles           #+#    #+#             */
/*   Updated: 2019/04/08 20:57:35 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "corewar.h"

static int		parse_ocp(t_op *op, uint8_t ocp, t_args *args)
{
	uint8_t		tmp;
	uint8_t		mask;
	size_t		i;

	mask = 0xc0;
	i = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		tmp = (ocp & mask) >> ((3 - i) * 2);
		if (tmp == REG_CODE && (op->params[i] & T_REG) != 0)
			args->type[i] = e_reg;
		else if (tmp == IND_CODE && (op->params[i] & T_IND) != 0)
			args->type[i] = e_ind;
		else if (tmp == DIR_CODE && (op->params[i] & T_DIR) != 0)
			args->type[i] = e_dir;
		else if (tmp == 0 && op->params[i] == 0)
			;
		else
			return (0);
		mask >>= 2;
		i++;
	}
	return (1);
}

static void		read_reg(t_int_types *arg, t_args *args, uint16_t pc, t_vm *vm)
{
	uint8_t	reg;

	reg = read1_memory(vm, pc) - 1;
	if (reg < 0 || reg >= REG_NUMBER)
	{
		args->false_ocp = 1;
		if (vm->verbose == 3)
			ft_printf("bad registrer number: %d, going "
			"to the next operation.\n", reg);
	}
	else
		(*arg).u_reg = reg;
}

static uint16_t	return_bad_ocp(t_args *args, t_vm *vm, uint16_t pc, uint8_t ocp)
{
	args->false_ocp = 1;
	if (vm->verbose == 3)
		ft_printf("bad ocp: %d, going to the next operation.\n", ocp);
	return (pc);
}

static uint16_t	get_params_ocp(uint16_t pc, t_vm *vm, t_op *op, t_args *args)
{
	uint8_t	ocp;
	int		i;

	ocp = read1_memory(vm, pc++);
	i = 0;
	if (parse_ocp(op, ocp, args) == 0)
		return (return_bad_ocp(args, vm, pc, ocp));
	while (i < op->nb_params)
	{
		if (args->type[i] == e_reg)
			read_reg(&args->value[i], args, pc++, vm);
		else if (args->type[i] == e_ind)
			args->value[i].u_ind = read2_memory(vm, pc);
		else if (args->type[i] == e_dir && op->little_dir == 1)
			args->value[i].u_dir16 = read2_memory(vm, pc);
		else if (args->type[i] == e_dir && op->little_dir == 0)
			args->value[i].u_dir32 = read4_memory(vm, pc);
		else
			crash(NULL, "wtf this should never be reached");
		if (args->type[i] != e_reg)
			pc += (args->type[i] == e_dir && op->little_dir == 0) ? 4 : 2;
		i++;
	}
	return (pc);
}

uint16_t		read_args(t_op *op, t_process *process, t_args *args, t_vm *vm)
{
	uint16_t	pc;

	pc = process->program_counter + 1;
	args->false_ocp = 0;
	args->false_reg = 0;
	if (op->ocp == 1)
		pc = get_params_ocp(pc, vm, op, args);
	else if (op->params[0] == T_DIR && op->little_dir == 1)
	{
		args->value[0].u_dir16 = read2_memory(vm, pc);
		pc += 2;
	}
	else if (op->params[0] == T_DIR && op->little_dir == 0)
	{
		args->value[0].u_dir32 = read4_memory(vm, pc);
		pc += 4;
	}
	else if (op->params[0] == T_REG)
		read_reg(&args->value[0], args, pc++, vm);
	else
		crash(process, "wtf this should never be reached");
	return (pc);
}
