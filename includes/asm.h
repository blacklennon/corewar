/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:56:46 by llopez            #+#    #+#             */
/*   Updated: 2019/04/08 19:26:35 by pcarles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

#ifndef ASM_H
# define ASM_H

typedef	struct	s_binary
{
	size_t	size;
	uint8_t	*table;
}		t_binary;

char		**split_whitespaces(char *txt);
char		*read_file(char	*path);
int			check_args(int argc, char **argv);
uint8_t		*bytes_conv(uint32_t content, uint8_t *table);
int			write_in_file(char *path, char **data);
t_binary	*interpret(char **data);
char		*get_header(char **data, char *cmd_string);
char		*get_new_path(char *path);
uint32_t	get_prog_size(char **data);
int			print_binary(int fd, t_binary *bin);
uint8_t		*add_byte(uint8_t content, t_binary *bin);
int			where_is(char *str, int c);
void		save_label(char *data, int arg, char *name_of_label);
char		*ft_strjstr(char const *str, char const *search);
int32_t		swap_int32(int32_t value);
void		replace_by_space(unsigned int i, char *str);
int			label_pos(char *label, char **data);
uint8_t		*add_data(char **param, t_binary *bin, int i_op_tab, char **data);
uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin, char **data);
int			find_op(char *str);
int			check_file(char *file);

#endif
