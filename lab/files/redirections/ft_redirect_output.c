/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:04:08 by rimney            #+#    #+#             */
/*   Updated: 2022/06/25 02:12:46 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


void	ft_single_redirect(char *argv)
{
	// int fd;

	// fd = open(argv, O_RDWR , 0644);
	printf("%s\n", argv);
}

void	ft_advanced_redirect(t_exec *exec, char **envp, int i, t_pipe *tpipe)
{
	int	fd;
	char **cmd_parser;
	int pid;

	tpipe->max = 0;
	cmd_parser = ft_split(exec->command[i - 1], ' ');
	printf("%s >>\n", exec->command[i - 1]);
	fd = open(exec->command[i + 1], O_CREAT | O_RDWR | O_TRUNC , 0644);
	dup2(tpipe->in_save, 0);
	close(tpipe->in_save);
	dup2(fd, 1);
	close(fd);
	pid = fork();
	if(pid == 0)
	{
		if(execve(ft_exec_command(envp, cmd_parser[0]), cmd_parser, envp) == -1)
		{
			printf("wrong shit --> %s\n", cmd_parser[0]);
		}
	}
	else
	{
		close(0);
		waitpid(pid, 0, 0);
		ft_free(cmd_parser);
	}
//	free(command);
}

int	ft_redirect(int index, t_exec *exec, int command_location)
{
	int fd;
	int pid;

	while(index < exec->redirection_count)
	{
		fd = open(exec->command[index + 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
		//printf("%s <<\n", exec->command[index + 1]);
		if(index + 1 == exec->redirection_count)
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
// 		add_history(line);
// 		if(ft_strcmp(line, "history") == 0)
// 			printf("h\n");
//       	ft_redirect(ft_count_elements(line_parser), line_parser, envp);
// 	  		ft_free(line_parser);
//      		free(line);
// 	}	
// 	return (0);
// }