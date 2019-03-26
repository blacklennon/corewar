/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:56:46 by llopez            #+#    #+#             */
/*   Updated: 2019/03/26 14:33:19 by llopez           ###   ########.fr       */
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
int		write_header(int fd, char **data, char *cmd_str, int size);
uint32_t	get_prog_size(char **data);
int		print_binary(int fd, t_binary *bin);
uint8_t		*add_byte(uint8_t content, t_binary *bin);
int		where_is(char *str, int c);
int		lexer(char **data);
int		tokenisation(int i, char **data, t_token *token,\
			 t_token *token_new);
int		is_label(char  *str);
void		addlist(t_token *token, t_token *token_new, int arg,\
			 char *data);
void		save_label(char *data, int arg, char *name_of_label);
int		ft_str_is_number(char *str);
int		ft_ratoi(char const *s);
void		addlist_opcode(int type, t_token *token, t_token *token_new);

#endif
