/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 01:34:10 by rimney            #+#    #+#             */
/*   Updated: 2022/05/30 05:58:52 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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



int ft_find_variable_index(char *str, char c)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == c)
            return (i);
        i++;
    }
    return (0);
}

int	ft_count_elements(char **str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

void	ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	ft_unset(char *str, t_env *env)
{
	int i;
	int unset;
	char **temp;
	int j;

	unset = 0;
	i = 0;
	temp = NULL;	
	while(env->envp[i])
	{
		if(ft_strncmp(str, env->envp[i], ft_find_variable_index(env->envp[i], '=')) == 0)
			unset = i;
		i++;
	}
	j = 0;
	i = 0;
	if(unset)
	{
		temp = malloc(sizeof(char *) * ft_count_elements(env->envp));
		while(env->envp[i])
		{
			if(j == unset)
				i++;
			temp[j] = strdup(env->envp[i]);
			i++;
			j++;
		}
	}
	temp[j] = 0;
	ft_free(env->envp);
	env->envp = temp;
}


int	main(int argc, char **argv, char **envp)
{
	char *line;
	char **line_parser;
	t_env env;

	ft_get_env(&env, envp);
	while((line = readline("unset > ")))
	{
		line_parser = ft_split(line, ' ');
		if(ft_strcmp(line, "env") == 0)
			ft_env(&env);
		 if(ft_strcmp(line_parser[0], "unset") == 0)
			ft_unset(line_parser[1], &env);
	}
}