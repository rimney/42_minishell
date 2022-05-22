/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 20:57:49 by rimney            #+#    #+#             */
/*   Updated: 2022/05/22 02:29:00 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/rimney/Desktop/Minishell/minishell.h"

int ft_get_last_delimiter(int argc, char **argv, int index)
{
    int i;
    int delimiter;


    i = index;
    delimiter = 0;
    while(i < argc)
    {
        if(ft_strcmp(argv[i], "<<") == 0)
            delimiter = i;
        i++;
    }
    return (delimiter);
}

int ft_exec_heredoc(char **argv, char **envp, int index, int fd[2])
{
    char *delimiter;
    char *line;
	char **command_2D;

    delimiter = strdup(argv[index + 1]);
    line = readline("geredoc1 >> ");
    while(ft_strcmp(line, delimiter) != 0)
    {
        line = readline("hereddoc> ");
        write(fd[1],line,strlen(line));
        write(fd[1], "\n", 1);
        if(ft_strcmp(line, delimiter) == 0)
        {
            close(fd[1]);
            dup2(fd[0], 0);
           close(fd[0]);
			command_2D = ft_split(argv[1], ' ');
          	  execve(ft_exec_command(envp, argv[1]), command_2D, envp);
            return (1);
        }
        free(line);
    }
    free(delimiter);
    return(0); 
}

void ft_heredoc(int argc, char **argv, char **envp, int index)
{
    int i;
    int pid;

    i = 1;
    int fd[2];
    pipe(fd);
    pid = fork();
    if(pid == 0)
        ft_exec_heredoc(argv, envp, ft_get_last_delimiter(argc, argv, 0), fd);
    else
        waitpid(pid, 0, 0);
    close(fd[0]);
    close(fd[1]);
}

int main(int argc, char **argv, char **envp)
{
    if(ft_get_last_delimiter(argc, argv, ))
    ft_heredoc(argc, argv, envp, 0);
    return (0);
}