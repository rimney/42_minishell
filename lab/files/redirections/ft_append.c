/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:23:26 by rimney            #+#    #+#             */
/*   Updated: 2022/06/09 22:05:40 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

// void	ft_advanced_append(int argc, char **argv, char **envp, int i)
// {
// 	int	fd;
// 	char **cmd_parser;
// 	char *command;
// 	int pid;

// 	cmd_parser = ft_split(argv[0], ' ');
// 	fd = open(argv[i + 1], O_CREAT | O_RDWR | O_APPEND , 0644);
// 	dup2(fd, STDOUT_FILENO);
// 	close(0);
// 	execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp);
// 	else
// 	{
// 		close(fd);
// 		waitpid(pid, 0, 0);
// 	}
// }

int	ft_append(int index, t_exec *exec, t_pipe *tpipe, int command_location)
{
	int pid;
	int fd;

	// if(argc == 1 && ft_strcmp(argv[0], ">>") == 0)
	// 	ft_single_append(argc, argv);
	tpipe->fd[0] = 0;
	while(index < exec->append_count)
	{
		fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if(index + 1 == exec->append_count)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(fd, 1);
				ft_execute_command(exec, command_location);
				close(fd);
			}
		}
		index += 2;
	}
	wait(NULL);
	return (index);
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
// 		// add_history(line);
// 		// if(ft_strcmp(line, "history") == 0)

//       		ft_append(ft_count_elements(line_parser), line_parser, envp);
// 	  	ft_free(line_parser);
//      	free(line);
// 	}	
// 	return (0);
// }
