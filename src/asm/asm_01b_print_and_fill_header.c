/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_02_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:22:22 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 13:22:54 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "asm.h"

void		fill_header(t_header *header, char **data, t_binary *table)
{
	char	*tmp;

	tmp = get_header(data, NAME_CMD_STRING);
	ft_bzero(header, sizeof(t_header));
	header->magic = swap_int32(COREWAR_EXEC_MAGIC);
	ft_strcpy(header->prog_name, tmp);
	free(tmp);
	tmp = get_header(data, COMMENT_CMD_STRING);
	ft_strcpy(header->comment, tmp);
	header->prog_size = swap_int32(table->size);
	free(tmp);
}

void		print_all(t_header *header, char *name, t_binary *table, int fd)
{
	write(1, "Writing output program to ", 26);
	write(fd, header, sizeof(t_header));
	print_binary(fd, table);
	write(1, name, ft_strlen(name));
	write(1, "\n", 1);
}
