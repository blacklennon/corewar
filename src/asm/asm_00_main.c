/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_00_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 12:38:08 by jdouniol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_printf.h"
#include "common.h"
#include "op.h"
#include "asm.h"

char		*read_file(int fd)
{
	int		i;
	char	buff[BUFFER_SIZE + 1];
	char	*tmp;
	char	*content;

	i = 0;
	tmp = NULL;
	content = NULL;
	errno = 0;
	while ((i = read(fd, buff, BUFFER_SIZE)) > 0)
	{
		buff[i] = '\0';
		if (i && content && ft_strlen(content))
		{
			tmp = ft_strdup(content);
			if (content)
				free(content);
			content = (char *)malloc(i + ft_strlen(tmp) + 1);
			content = ft_strcpy(content, tmp);
			content = ft_strcat(content, buff);
			free(tmp);
		}
		else if (i)
			content = ft_strdup(buff);
		if (i < BUFFER_SIZE)
			return (content);
	}
	if (i < 0)
		perror("asm");
	return (content);
}

int			write_in_file(char *path, char **data)
{
	int			fd;
	char		*tmp;
	char		*name;
	t_binary	*table;
	t_header	header;

	table = NULL;
	name = get_new_path(path);
	if (name)
	{
		if (!(table = interpret(data)))
		{
			write(1, "\033[41m Error occured \033[0m\n", 24);
			return (0);
		}
		tmp = get_header(data, NAME_CMD_STRING);
		ft_bzero(&header.magic, sizeof(header));
		header.magic = swap_int32(COREWAR_EXEC_MAGIC);
		ft_strcpy(header.prog_name, tmp);
		free(tmp);
		tmp = get_header(data, COMMENT_CMD_STRING);
		ft_strcpy(header.comment, tmp);
		header.prog_size = swap_int32(table->size);
		if ((fd = open(name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)))
		{
			write(1, "Writing output program to ", 26);
			write(fd, &header, sizeof(header));
			print_binary(fd, table);
			write(1, name, ft_strlen(name));
			write(1, "\n", 1);
		}
		free(table->table);
		free(table);
		free(tmp);
	}
	free(name);
	fd = 0;
	return ((name) ? 1 : 0);
}

int			main(int argc, char **argv)
{
	char	*file;
	char	**data;
	int		i;
	int		fd;
	char	*tmp;

	i = 0;
	file = NULL;
	if (argc < 2)
		exit(EXIT_FAILURE);
	fd = check_args(argv[1]);
	file = read_file(fd);
	if (!check_file(file))
	{
		ft_printf("\033[41m Invalid file \033[0m\n");
		free(file);
		return (EXIT_FAILURE);
	}
	data = ft_strsplit(file, '\n');
	while (data[i])
	{
		tmp = ft_strtrim(data[i]);
		free(data[i]);
		data[i] = tmp;
		i++;
	}
	write_in_file(argv[1], data);
	i = 0;
	while (data[i])
		free(data[i++]);
	free(data);
	free(file);
	return (EXIT_SUCCESS);
}
