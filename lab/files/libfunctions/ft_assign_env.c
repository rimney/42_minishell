/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_assign_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:32:58 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 15:33:42 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void    ft_get_env(t_env *env, char **envp)
{
    int i;

    i = 0;
    env->envp = malloc(sizeof(char *) * ft_count_elements(envp) + 1);
    while(i < ft_count_elements(envp))
    {
        env->envp[i] = strdup(envp[i]);
        i++;
    }
    env->envp[i] = 0;
    i = 0;
    while(i < ft_count_elements(envp))
    {
        if(ft_strncmp(envp[i], "PWD=", 4) == 0)
           env->pwd = strdup(envp[i]);
        i++;
    }
} 