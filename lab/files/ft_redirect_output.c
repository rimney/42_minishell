/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:04:08 by rimney            #+#    #+#             */
/*   Updated: 2022/05/19 04:32:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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

// void	ft_free(char **value)
// {
// 	int i;

// 	i = 0;
// 	while (value[i])
// 	{
// 		free(value[i]);
// 		i++;
// 	}
// 	free(value);
// }


void	ft_advanced_redirect(int argc, char **argv, char **envp, int i)
{
	int	fd;
	char *command;
	char **cmd_parser;
	
	command = ft_exec_command(argv[0], envp, argv);
	cmd_parser = ft_split(argv[0], ' ');
	fd = open(argv[i + 1], O_CREAT | O_RDWR | O_TRUNC , 0644);
	dup2(fd, STDOUT_FILENO);
	if(execve(command, cmd_parser, envp) == -1)
	{
		printf("%s <\n", argv[0]);
		printf("wrong shit --> %s\n", command);
	}
	//close(fd);
//	waitpid(pid, 0, 0);
}

int	ft_redirect(int argc, char **argv, char **envp)
{
	int fd;
	char *line;
	int i = 0;
	int pid;

	if(argc == 1 && ft_strcmp(argv[0], ">") == 0)
	{
		printf("ahahah\n");
		ft_single_redirect(argc, argv);
	}
	else
	{
			while(i < argc)
			{
				if(ft_strcmp(argv[i], ">") == 0)
				{
					// pid = fork();
					// if(pid == 0)
						ft_advanced_redirect(argc, argv, envp, i);
					waitpid(pid, 0, 0);
				}
				i++;
		//	printf("%d <<\n", i);
			}
	}
	return (0);
}

// int	ft_count_elements(char **str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int main(int argc, char **argv, char **envp)
{
	char *line;
	char **line_parser;
	int pid;
	char *history;

	while((line = readline("Minishell >> ")))
	{
		line_parser = ft_split(line, ' ');
		add_history(line);
		if(ft_strcmp(line, "history") == 0)
			printf("h\n");
		else
    	{
      		pid = fork();
      		if (pid == 0)
      			ft_redirect(ft_count_elements(line_parser), line_parser, envp);
	  		ft_free(line_parser);
     		free(line);
     		waitpid(pid, 0, 0);
		}
	}	
	return (0);
}
// int	main(int argc, char **argv, char **envp)
// {
// 	ft_redirect(argc, argv, envp);
// 	return (0);
// }