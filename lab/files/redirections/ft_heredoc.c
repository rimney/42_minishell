/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 01:54:28 by rimney            #+#    #+#             */
/*   Updated: 2022/06/23 01:28:40 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int ft_get_last_delimiter(t_exec *exec, int index)
{
    int i;
    int delimiter;


    i = index;
    delimiter = 0;
    while(i < exec->args)
    {
        if(ft_strcmp(exec->command[i], "<<") == 0)
            delimiter = i;
        i++;
    }
    return (delimiter);
}

int ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_loaction)
{
    char *delimiter;
    char *line;


    delimiter = strdup(exec->command[index + 1]);
    while((line = readline("heredoc > ")))
    {
        if (ft_strcmp(line, delimiter) != 0)
        {
            write(fd[1],line,strlen(line));
            write(fd[1], "\n", 1);
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            close(fd[1]);
            dup2(fd[0], 0);
           close(fd[0]);
            ft_execute_command(exec, command_loaction);
            return (1);
        }
        free(line);
    }
    free(delimiter);
    return(0); 
}

void ft_heredoc(t_exec *exec, int command_location)
{
    int i;
    int pid;

    i = 1;
    int fd[2];
    pipe(fd);
    pid = fork();
    if(pid == 0)
        ft_exec_heredoc(exec, ft_get_last_delimiter(exec, 0), fd, command_location);
    else
    {
        close(fd[0]);
        close(fd[1]);
        waitpid(pid, 0, 0);
    }
 
}

int ft_basic_heredoc(t_exec *exec, int index)
{
    char *line;
    char *delimiter;

    delimiter = strdup(exec->command[index + 1]);
    while((line = readline("heredoc_basic >")))
    {
        if(ft_strcmp(line, delimiter) == 0)
        {
            free(delimiter);
            free(line);
            return (1);
        }
        free(line);
    }
    return (0);
}

void    ft_advanced_heredoc(t_exec *exec, int index, int command_location)
{
    int i;

    i = index;
    while (i < ft_get_last_delimiter(exec,  0))
    {
        if (ft_strcmp(exec->command[i], "<<") == 0)
            ft_basic_heredoc(exec, i);
        i++;
    }
    if (i == ft_get_last_delimiter(exec, 0))
    {
        ft_heredoc(exec, command_location);
    }
        
    
}

int ft_execute_heredoc(t_exec *exec, t_pipe *pipes, int index)
{
    int command_location;

    command_location = index - 1;
    pipes->fd[0] = 0;
    if(ft_get_last_delimiter(exec, 0) == 1)
        ft_heredoc(exec, command_location);
    else
        ft_advanced_heredoc(exec, index, command_location);
    return (0);
}

