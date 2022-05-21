/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 20:02:42 by rimney            #+#    #+#             */
/*   Updated: 2022/05/21 03:21:47 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    redirect(int argc, char **argv, char **envp, int index)
{
    char *command;
    char **command_parser;
    int fd;
    int fd2;

    fd = open(argv[argc - 1], O_RDONLY);
     command_parser = argv + index + 1;

    command = ft_exec_command(envp, argv[0]);
    dup2(fd, 0);
    close(fd);
    execve(command, command_parser, envp);
    
}

int    ft_redirect_input(int argc, char **argv, char **envp)
{
    int i;
    int input_file;
    int pid;

    i = 0;
    while(i < argc)
    {
        input_file = open(argv[argc - 1], O_RDONLY);
        if(input_file == -1)
        {
            perror("minishell ");
            return 0;
        }
        if(ft_strcmp(argv[i], "<") == 0)
        {
            pid = fork();
            if (pid == 0)
                redirect(argc, argv, envp, i);
            else
                waitpid(pid, 0, 0);
        }
        i++;
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
// 		else
//     	{
//       		pid = fork();
//       		if (pid == 0)
//       			ft_redirect_input(ft_count_elements(line_parser), line_parser, envp);
// 			else
// 			 waitpid(pid, 0, 0);
// 	  		ft_free(line_parser);
//      		free(line);
// 		}
// 	}	
// 	return (0);
// }