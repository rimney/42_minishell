/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 17:56:38 by rimney            #+#    #+#             */
/*   Updated: 2022/06/14 02:07:35 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    ft_execute_command(t_exec *exec, int index)
{
    char **command_parser;

    command_parser = ft_split(exec->command[index], ' ');
        if(execve(ft_exec_command(exec->env.envp, command_parser[0]), command_parser, exec->env.envp) == -1)
        {
            printf(">>>| %s |<<<\n", command_parser[0]);
            perror("Minishell : ");
            ft_free(command_parser);
            exit(127); // shoud put exit value in here;
        }
    else
    {
        ft_free(command_parser);

    }
}

