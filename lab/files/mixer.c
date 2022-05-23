/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:24:48 by rimney            #+#    #+#             */
/*   Updated: 2022/05/23 23:40:16 by rimney           ###   ########.fr       */
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

int ft_find_variable_index(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}


void    ft_export(t_env *env, char *argument)
{
    int i;
    int j;
    char **temp;

    i = 0;
    temp = env->envp;
    env->envp = malloc(sizeof(char *) * ft_count_elements(env->envp) + 1 + 1);
    if(ft_find_variable_index(argument))
	{
		while(temp[i])
		{
			env->envp[i] = strdup(temp[i]);
			i++;
		}
		env->envp[i] = strdup(argument);
		printf("| %s |\n", env->envp[i]);
		env->envp[i + 1] = 0;
	}
	//ft_free(temp);
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
    if(flag == 0)
    {
	    ft_export(env, argv[1]);
        // ft_env(env);
    }
    if(flag == 1)
    ft_env(env);

	return (0);
}


int main(int argc, char **argv, char **envp)
{
    char *line;
    char **line_parser;
    t_env env;
    ft_get_env(&env, envp);
    while((line = readline("line >")))
    {
        line_parser = ft_split(line ,' ');
        if(ft_strcmp(line, "env") == 0)
            ft_mixer(argc, line_parser, &env, 1);
        if(ft_strcmp(line_parser[0], "export") == 0)
            ft_mixer(argc, line_parser, &env, 0);
        free(line);
    }
    return (0);
}
