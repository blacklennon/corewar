/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_00_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdouniol <jdouniol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/04/12 17:35:31 by llopez           ###   ########.fr       */
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

char		*ft_concat(char *content, int i, char *buff)
{
	char	*tmp;

	tmp = ft_strdup(content);
	if (content)
		free(content);
	content = (char *)malloc(i + ft_strlen(tmp) + 1);
	content = ft_strcpy(content, tmp);
	content = ft_strcat(content, buff);
	free(tmp);
	return (content);
}

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
		if (!ft_str_is_ascii(buff))
			return (NULL);
		if (i && content && ft_strlen(content))
			content = ft_concat(content, i, buff);
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
			free(name);
			free(table);
			return (0);
		}
		fill_header(&header, data, table);
		if ((fd = open(name, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)))
			print_all(&header, name, table, fd);
		free(table->table);
		free(table);
	}
	free(name);
	return ((name) ? 1 : 0);
}

void		asm_usage(void)
{
	ft_printf("usage:\t./asm file.s\n");
	exit(EXIT_FAILURE);
}

int			main(int argc, char **argv)
{
	char	*file;
	char	**data;
	int		i;
	int		fd;

	i = 0;
	file = NULL;
	if (argc < 2 || argc > 2)
		asm_usage();
	fd = check_args(argv[1]);
	file = read_file(fd);
	if (!check_file(file))
	{
		write(1, "\033[41m Invalid file \033[0m\n", 24);
		free(file);
		return (EXIT_FAILURE);
	}
	data = ft_strsplit(file, '\n');
	clean_data(data);
	write_in_file(argv[1], data);
	while (data[i])
		free(data[i++]);
	free(data);
	free(file);
	return (EXIT_SUCCESS);
}
