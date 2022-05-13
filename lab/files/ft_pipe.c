/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 21:31:21 by rimney            #+#    #+#             */
/*   Updated: 2022/05/13 19:02:18 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void    pipe(char **argv, int index, int *fd)
{
    int pid;
    char **cmd1_parser;
    char **cmd2_parser;

    cmd1_parser = ft_split(argv[index - 1], ' ');
    cmd2_parser = ft_split(argv[index + 1], ' ');
    if(pipe[fd) == -1])
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

void    ft_pipe(int argc, char **argv, char **envp, int pipes)
{
    int *fd[2];
    int i;

    i = 1;
    *fd = malloc(sizeof(int *) * pipes);
    while(i < argc)
    {
        if(pid == 0)
        {
            dup2(fd[1], 1);
            execve(ft_exec_command(argv[index - 1], envp, argv), cmd1_parser, envp);
        }
}


void    ft_pipes(int argc, char **argv, char **envp)
{
    int i = 1;
    int pid;
    int npipes;
    int j = 1;

    npipes = 0;
    while(j < argc)
    {
        if(ft_strcmp(argv[j], "|") == 0)
            npipes += 1;
        j++;
    }
    if(npipes > 1)
    {
        ft_pipes(argc, argv, npipes)
    }
    printf("%d P<\n", npipes);
}

int main(int argc, char **argv, char **envp)
{
    ft_pipes(argc, argv, envp);
    return (0);
}