/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/20 03:15:34 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_single_append(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">>") == 0)
	{
		fd = open(argv[2], O_CREAT | O_RDWR, 0644);
		while(1)
		{
			fd = open(argv[2], O_RDWR | O_APPEND, 0644);
			line = readline("");
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

void	ft_advanced_append(int argc, char **argv, char **envp, int i)
{
	int	fd;
	char **cmd_parser;

	cmd_parser = ft_split(argv[0], ' ');
	fd = open(argv[i + 1], O_CREAT | O_RDWR | O_APPEND , 0644);
	dup2(fd, STDOUT_FILENO);
	execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp);
	close(fd);
}

int	ft_append(int argc, char **argv, char **envp)
{
	int fd;
	char *line;
	int i = 1;
	int pid;

	if(argc == 3 && ft_strcmp(argv[1], ">>") == 0)
		ft_single_append(argc, argv);
	else
	{
			while(i < argc)
			{
				if(ft_strcmp(argv[i], ">>") == 0)
				{
					pid = fork();
					if(pid == 0)
						ft_advanced_append(argc, argv, envp, i);
				}
				i++;
			printf("%d <<\n", i);
			waitpid(pid, 0, 0);
			}
	}
	return (0);
}