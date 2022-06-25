/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:32:58 by rimney            #+#    #+#             */
/*   Updated: 2022/06/25 01:51:04 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    ft_get_env(t_exec *exec, char **env)
{
    int     i;

    i = 0;
    exec->envp = malloc(sizeof(char *) * ft_count_elements(env) + 1);
    while(i < ft_count_elements(env))
    {
        exec->envp[i] = strdup(env[i]);
        i++;
    }
    exec->envp[i] = 0;
   // return (envp);
} 