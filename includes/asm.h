/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:56:46 by llopez            #+#    #+#             */
/*   Updated: 2019/03/19 18:45:25 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

char		**split_whitespaces(char *txt);
char		*read_file(char	*path);
int			check_args(int argc, char **argv);
uint8_t		*bytes_conv(uint32_t content, uint8_t *table);
int			write_in_file(char *path, char **data);
uint32_t	*interpret(char **program, int fd);

#endif
