/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:04:08 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 16:55:58 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


void	ft_single_redirect(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">") == 0)
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

void	ft_advanced_redirect(t_exec *exec, char **envp, int i)
{
	int	fd;
	char **cmd_parser;
	int pid;

	cmd_parser = ft_split(exec->command[i - 1], ' ');
	pid = fork();
	if(pid == 0)
	{
		fd = open(exec->command[i + 1], O_CREAT | O_RDWR | O_TRUNC , 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if(execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp) == -1)
		{
			printf("wrong shit --> %s\n", cmd_parser[0]);
		}
		close(0);
	}
	else
		waitpid(pid, 0, 0);
	ft_free(cmd_parser);
//	free(command);
}

int	ft_redirect(int argc, char **argv, char **envp)
{
	int fd;
	int i;
	int pid;

	i = 0;
	if(argc == 1 && ft_strcmp(argv[0], ">") == 0)
		ft_single_redirect(argc, argv);
	else
	{
		while(i < argc)
		{
			if(ft_strcmp(argv[i], ">") == 0)
			{
				pid = fork();
				if(pid == 0)
				{
					fd = open(argv[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
					dup2(fd, 1);
					execve(ft_exec_command(envp, argv[0]), ft_split(argv[0], ' '), envp);
					close(fd);
				}
				else
					waitpid(pid, 0, 0);
			}
			i++;
		}
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char *line;
// 	char **line_parser;
// 	int pid;
// 	char *history;

// 	while((line = readline("Minishell >> ")))
// 	{
// 		line_parser = ft_split(line, ' ');
// 		add_history(line);
// 		if(ft_strcmp(line, "history") == 0)
// 			printf("h\n");
//       	ft_redirect(ft_count_elements(line_parser), line_parser, envp);
// 	  		ft_free(line_parser);
//      		free(line);
// 	}	
// 	return (0);
// }