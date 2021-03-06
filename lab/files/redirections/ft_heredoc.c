/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 01:54:28 by rimney            #+#    #+#             */
/*   Updated: 2022/06/25 01:16:58 by rimney           ###   ########.fr       */
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
    int out;
    
    out  = -1;
    delimiter = strdup(exec->command[index + 1]);
    if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == REDIROUT)
    {
        exec->redirection_count = ft_count_till_other_token(exec, index + 2, ">");
         out = open(exec->command[index + exec->redirection_count + 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
       //  exec->heredoc_count;
    }
        
    while((line = readline("heredoc > ")))
    {
        if (ft_strcmp(line, delimiter) != 0)
        {
            write(fd[1],line,strlen(line));
            write(fd[1], "\n", 1);
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            if(out != -1)
            {
                dup2(out, 1);
                close(out);
            }
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

void ft_heredoc(t_exec *exec, int command_location, int index)
{
    int i;
    int pid;

    i = 1;
    printf("%s <<<<<<< LAST\n", exec->command[ft_get_last_delimiter(exec, index - 1)]);
    int fd[2];
    pipe(fd);
    pid = fork();
    if(pid == 0)
        ft_exec_heredoc(exec, index, fd, command_location);
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
    printf("%s << index\n", exec->command[index]);
    // while (i < ft_get_last_delimiter(exec, index) && exec->heredoc_count > 2)
    // {
    //     if (ft_strcmp(exec->command[i], "<<") == 0)
    //         ft_basic_heredoc(exec, i);
    //     i++;
    // }
    ft_heredoc(exec, command_location, index);
        
    
}

int ft_execute_heredoc(t_exec *exec, t_pipe *pipes, int index)
{
    int command_location;

    command_location = index - 1;
    pipes->fd[0] = 0;

    if(exec->command[index + 2] && ft_is_another_flag(exec, index + 2) == PIPE)
    {
        printf("FLAAAAGGG\n");
        ft_basic_heredoc(exec, index);
        return (1);
    }
    else if(ft_strcmp(exec->command[index], "<<") == 0 && exec->command[index + 2] == NULL)
    { 
        printf("FLAAAAAAGGGGG\n");
        ft_heredoc(exec, command_location, index);
        return (1);
    }
    else
    {
        ft_advanced_heredoc(exec, index, command_location);
        return (1);
    }
    return (0);
}