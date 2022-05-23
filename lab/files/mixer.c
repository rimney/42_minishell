/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:24:48 by rimney            #+#    #+#             */
/*   Updated: 2022/05/23 02:17:54 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env    *ft_get_env(t_env *env, char **envp)
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
    return (env);
} 




void    ft_cd(t_env *env, char *path)
{
    
}

int ft_mixer(int argc, char **argv, char **envp)
{
    int i;
    int j;
    t_env *env;

    i = 0;
    env = ft_get_env(env, envp);
    ft_cd(env, argv[2]);
    return (0);
}


int main(int argc, char **argv, char **envp)
{
    while(1)
    {
        ft_mixer(argc, argv, envp);
    return (0);
}
