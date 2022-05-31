/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 01:16:51 by rimney            #+#    #+#             */
/*   Updated: 2022/05/31 19:16:13 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int    ft_merge(int argc, char **argv, t_env *env)
{
    int i;

    i = 0;
    while (i < argc)
    {
        if(ft_strcmp(argv[1], "<") == 0)
        {
            ft_redirect_input(argc, argv, env->envp);
            return 1;
        }
        // else if(ft_strcmp(argv[i], "<<") == 0)
        // {
        //     ft_execute_heredoc(argc, argv, env->envp);
        //     return (1);
        // }
        // else if(ft_strcmp(argv[i], ">") == 0)
        // {
        //     ft_redirect(argc, argv, env->envp);
        //     return (1);
        // }
        // else if(ft_strcmp(argv[i], "<") == 0)
        // {
        //     ft_redirect_input(argc, argv, env->envp);
        //     return (1);
        // }
        // else
        // {
        //     execve(ft_exec_command(env->envp, argv[0]), argv, env->envp);
        // }
    }
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env env;

    ft_get_env(&env, envp);
    while((line = readline("Minishell >> ")))
    {
        ft_merge(ft_count_elements(ft_split(line, ' ')), ft_split(line, ' '), &env);
        free(line);
    }
}