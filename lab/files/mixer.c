/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:24:48 by rimney            #+#    #+#             */
/*   Updated: 2022/05/26 03:43:38 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int ft_count_elements(char **str)
// {
//   int i;

//   i = 0;
//   while(str[i])
//     i++;
//   return (i);
// }


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



int ft_find_variable_index(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return (i);
        i++;
    }
    return (0);
}


void	ft_echo(char *str, t_env *env, int flag) // i have no idea how this works !! 
{
	int i;

	i = 0;
	// printf("%s\n", str);
	while(str[i])
	{
		printf("%c", str[i++]);

	}
	if(flag)
	{
		printf("\n");
	}
}

int ft_mixer(int argc, char **argv, t_env *env, int flag)
{
    // if(flag == 0)
    // {
	//     ft_export(env, argv[1]);
    //     // ft_env(env);
    // }
    if(flag == 1)
    ft_env(env);

	return (0);
}


