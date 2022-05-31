/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 17:56:15 by rimney            #+#    #+#             */
/*   Updated: 2022/05/30 20:40:40 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int    ft_env(t_env *env)
{
    int i;

    i = 0;
    while(env->envp[i])
    {
        if(!env->envp[0])
        {
            printf("Path not found!!\n");
            return (0);
        }
        printf("%s\n", env->envp[i]);
        i++;
    }
    return (1);
}
