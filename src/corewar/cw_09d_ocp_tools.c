/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_09d_ocp_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 16:49:53 by pcarles           #+#    #+#             */
/*   Updated: 2019/03/27 22:24:27 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"
#include "corewar.h"

int				go_to_next_valid_op(t_vm *vm, uint16_t program_counter)
{
	int offset;
	int base;

	base = program_counter;
	offset = program_counter;
	while (vm->memory[offset % MEM_SIZE] < LIVE || vm->memory[offset % MEM_SIZE] > AFF)
		offset++;
	if (vm->memory[offset % MEM_SIZE] >= ADD && vm->memory[offset % MEM_SIZE] <= SUB)
    {
		if (vm->memory[(offset + 1) % MEM_SIZE] == 0x54)
			return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] >= AND && vm->memory[offset % MEM_SIZE] <= OR)
	{
    	if (ft_is_ocp_of_and_or_xor(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == LDI || vm->memory[offset % MEM_SIZE] == LLDI)
	{
        if (ft_is_ocp_of_ldi_lldi(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == LLD)
	{
    	if (ft_is_ocp_of_lld(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == LD)
	{
    	if (ft_is_ocp_of_ld(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == ST)
	{
    	if (ft_is_ocp_of_st(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == STI)
	{	
        if (ft_is_ocp_of_sti(vm, offset))
            return (offset - base);
    }
    else if (vm->memory[offset % MEM_SIZE] == LIVE || vm->memory[offset % MEM_SIZE] == ZJMP
        || vm->memory[offset % MEM_SIZE] == FORK || vm->memory[offset % MEM_SIZE] == LFORK
        || vm->memory[offset % MEM_SIZE] == AFF)
        return (offset);
    else
    {
        ft_printf("there is no more valid operation\n");
    }
    return (4);
}

int     ft_is_ocp_of_and_or_xor(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0x54
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xd4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x74
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xf4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x94
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x64
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xb4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xe4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xa4)
        return (1);
    else
        return (0);
}

int     ft_is_ocp_of_ldi_lldi(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0x54
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xd4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x94
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x64
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xe4
        || vm->memory[(offset + 1) % MEM_SIZE] == 0xa4)
        return (1);
    else
        return (0);
}

int     ft_is_ocp_of_sti(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0x54
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x74
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x64
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x58
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x78
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x68)
        return (1);
    else
        return (0);
}

int     ft_is_ocp_of_lld(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0xd0
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x90)
        return (1);
    else
        return (0);
}

int     ft_is_ocp_of_ld(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0xd0
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x90)
        return (1);
    else
        return (0);
}

int     ft_is_ocp_of_st(t_vm *vm, int offset)
{
    if (vm->memory[(offset + 1) % MEM_SIZE] == 0x50
        || vm->memory[(offset + 1) % MEM_SIZE] == 0x70)
        return (1);
    else
        return (0);
}