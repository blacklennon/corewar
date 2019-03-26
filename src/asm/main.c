/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llopez <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 15:11:44 by llopez            #+#    #+#             */
/*   Updated: 2019/03/26 14:33:19 by llopez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../lib/libft/includes/libft.h"
#include "../../includes/op.h"
#include "../../includes/asm.h"

char	*read_file(char	*path)
{
	int		fd;
	int		i;
	char	buff[4096];
	char	*tmp;
	char	*content;

	i = 0;
	tmp = NULL;
	content = NULL;
	if ((fd = open(path, O_RDONLY)))
	{
		while ((i = read(fd, buff, 4096)))
		{
			buff[i] = 0;
			if (i && content && ft_strlen(content))
			{
				if (tmp)
					free(tmp);
				tmp = ft_strdup(content);
				if (content)
					free(content);
				content = (char *)malloc((i + ft_strlen(tmp) + 1));
				content = ft_strcpy(content, tmp);
				content = ft_strcat(content, buff);
			}
			else if (i)
				content = ft_strdup(buff);
			if (i < 4096)
				return (content);
		}
	}
	return (content);
}

int		check_args(int argc, char **argv)
{
	if (argc >= 2 && open(argv[1], O_RDONLY) > 0)
		return (1);
	return (0);
}

int		write_in_file(char *path, char **data)
{
	int		fd;
	char		*newpath;
	uint8_t		tmp[4];
	t_binary	*table;

	table = NULL;
	newpath = get_new_path(path);
	if ((fd = open(newpath, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR)))
	{
		printf("output file : %s\n", newpath);
		bytes_conv((uint32_t)COREWAR_EXEC_MAGIC, tmp);
		write(fd, tmp, 4);
		write_header(fd, data, NAME_CMD_STRING, PROG_NAME_LENGTH);
		write_header(fd, data, COMMENT_CMD_STRING, COMMENT_LENGTH);
		table = interpret(data);
		print_binary(fd, table);
		free(table);
	}
	return (1);
}

char		*clean_comments(char *line)
{
	char	*tmp;

	tmp = NULL;
	printf("comment : \t%s\n", line);
	if (ft_strchr(line, COMMENT_CHAR))
		tmp = ft_strsub(line, 0, where_is(line, COMMENT_CHAR));
	if (tmp)
		free(line);
	printf("clean comment : %s\n", (tmp) ? tmp : line);
	return ((tmp) ? tmp : line);
}

int		main(int argc, char **argv)
{
	char	*file;
	char	**data;
	int	i;

	i = 0;
	file = NULL;
	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	file = read_file(argv[1]);
	data = ft_strsplit(file, '\n');
	write_in_file(argv[1], data);
	while (data[i])
		free(data[i++]);
	usleep(100000);
	return (EXIT_SUCCESS);
}
