/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 01:24:48 by rimney            #+#    #+#             */
/*   Updated: 2022/05/25 03:44:43 by rimney           ###   ########.fr       */
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
            return (i);
        i++;
    }
    return (0);
}

char    **ft_join_export(t_env *env, char *arg)
{
    int i;
    char **temp;

    i = 0;
    temp = env->envp;
    env->envp = (char **)malloc(sizeof(char *) * ft_count_elements(env->envp) + 1 + 1);
    if(ft_find_variable_index(arg))
	{
		while(temp[i])
		{
			env->envp[i] = strdup(temp[i]);
			i++;
		}
		env->envp[i] = strdup(arg);
		printf("| %s | has been joined  \n" , env->envp[i]);
		env->envp[i + 1] = 0;
	}
	return(env->envp);
}

void	ft_export_replace(t_env *env, char *arg, int index)
{
	char *temp;

	temp = env->envp[index];
	//printf("%s T\n", temp);
	env->envp[index] = strdup(arg);
	free(temp);
}

void	ft_export(t_env *env, char **argv, int index)
{
    int i;
	char **temp;
    int j = 0;
    temp = NULL;
    i = 0; 
	if(!ft_find_variable_index(argv[index + 1]))
		return ;
    while(env->envp[i])
	{
		if(ft_strncmp(argv[index + 1], env->envp[i], ft_find_variable_index(argv[index + 1])) == 0)
		{
			printf("%d\n", ft_find_variable_index(argv[index + 1]));
			ft_export_replace(env, argv[index + 1], i);
			printf("%s <- new\n", env->envp[i]);
			return ;
		}
		i++;
	}
	if(ft_find_variable_index(argv[index + 1]))
	{
        for ( j = 0; env->envp[j] != NULL ; j++)
        {
            ;
        }
        temp = malloc(sizeof(char *) * (j + 1 + 1));
        for ( j = 0; env->envp[j] != NULL ; j++)
        {
            temp[j] = strdup(env->envp[j]);
        }
        temp[j] =  argv[index + 1];
        temp[++j] = NULL;
        for(int c = 0; env->envp[c] != NULL; c++)
        {
            free(env->envp[c]);
        }
        free(env->envp);
		env->envp = temp;
       // for (int a= 0; env->envp[a] != NULL)
		//env->envp = ft_join_export(env, argv[index + 1]);
	}
    // if(temp[0] || !temp)
	//ft_free(temp);
    //printf("Export\n");
    //printf("%s\n",temp[0]);
    //printf("%s\n", argv[index + 1]);
    //ft_join_export(env, argv[index + 1]);
    
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
            ft_export(&env, line_parser, 0);
        free(line);
    }
    return (0);
}
