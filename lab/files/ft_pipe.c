/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:31:21 by rimney            #+#    #+#             */
/*   Updated: 2022/05/12 02:20:15 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void    ft_pipe(char **argv, char **envp, int index)
{
    int pid;
    int fd[2][2];
    char **cmd1_parser;
    char **cmd2_parser;

    cmd1_parser = ft_split(argv[index - 1], ' ');
    cmd2_parser = ft_split(argv[index + 1], ' ');
    if(pipe(fd) == -1)
        perror("minishell");
    pid = fork();
    if(pid == 0)
    {
        dup2(fd[1], 1);
        execve(ft_exec_command(argv[index - 1], envp, argv), cmd1_parser, envp);
    }
    close(fd[1]);
    dup2(fd[0], 0);   
    execve(ft_exec_command(argv[index + 1], envp, argv), cmd2_parser, envp);
    close(fd[0]);
     waitpid(pid, 0, 0);
}

// void    ft_pipe(char **argv, char **envp, int index)
// {
//     int fd[2];
//     int p1;
//     int p2;
//     char **cmd1_parser;
//     char **cmd2_parser;

//     cmd1_parser = ft_split(argv[index - 1], ' ');
//     cmd2_parser = ft_split(argv[index + 1], ' ');
//     pipe(fd);
//     p1 = fork();
//     if(p1 == 0)
//     {
//         dup2(fd[1], 1);
//         execve(ft_exec_command(argv[index - 1], envp, argv), cmd1_parser, envp);
//         close(fd[0]);
//         close(fd[1]);
//     }
//     p2 = fork();
//     if(p2 == 0)
//     {
//         dup2(fd[0], 0);
//         execve(ft_exec_command(argv[index + 1], envp, argv), cmd2_parser, envp);
//         close(fd[0]);
//         close(fd[1]);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     waitpid(p1, 0, 0);
//     waitpid(p2, 0, 0);

// }

void    ft_pipes(int argc, char **argv, char **envp)
{
    int i = 1;
    int pid;
    while(i < argc)
    {
        if(ft_strcmp(argv[i], "|") == 0)
        {
            pid = fork();
            if(pid == 0)
            ft_pipe(argv, envp, i);
           // waitpid(pid, 0, 0);
        }
        i++;
     //   printf("%d<<\n", i);
    }
}

int main(int argc, char **argv, char **envp)
{
    ft_pipes(argc, argv, envp);
    return (0);
}