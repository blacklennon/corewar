/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcarles <pcarles@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:56:46 by llopez            #+#    #+#             */
/*   Updated: 2019/04/10 22:47:55 by llopez           ###   ########.fr       */
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
void		replace_by_space(unsigned int i, char *str);
int			label_pos(char *label, char **data);
uint8_t		*add_data(char **param, t_binary *bin, int i_op_tab, char **data);
uint8_t		*add_param(char	*str, int i_op_tab, t_binary *bin, char **data);
int			find_op(char *str);
int			check_file(char *file);
size_t		param_size(char *str);
int			ft_labelcmp(char *label, char *str);
int			ft_cbc(char *file, char a, char b);
void		delete_comment(char *str);
char		*jump_spaces(char *file);
int			check_name_comment(char *file);
char		*ft_strjstr_line(char const *str, char const *search);
int			find_op_line(char *str);
int			find_label(char *label_name, char *file);
int			ft_valid_number(char *file);
int			check_param(int	op_code, char *file, char *start);
char		*jump_header(char *file);
int			check_char_label(char *label_name);
char		*check_label(char *file);
int			check_all(char *file);
int			check_file(char *file);

#endif
