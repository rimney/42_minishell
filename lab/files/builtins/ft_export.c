/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 02:59:30 by rimney            #+#    #+#             */
/*   Updated: 2022/05/30 20:40:37 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	char	*tmp;
	i = 0;
	while (tab[i] != 0)
	{
		j = i;
		while (tab[j] != 0)
		{
			if (ft_strcmp(tab[i], tab[j]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[j];
				tab[j] = tmp;
			}
			j++;
		}
		i++;
	}
}



void    ft_export_no_args_case(t_env *env)
{
    char **temp;
    int i;

    i = 0;
    temp = malloc(sizeof(char *) * ft_count_elements(env->envp) + 1);
    while(env->envp[i])
    {
        temp[i] = strdup(env->envp[i]);
        i++;
    }
    temp[i] = 0;
    ft_sort_string_tab(temp);
    i = 0;
    while(temp[i])
    {
        printf("declare -x %s\n", temp[i]);
        i++;
    }
    ft_free(temp);
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
    int flag;


    flag = 0;
    if(arg[ft_find_variable_index(arg) + 1]  == '\"')
        flag = 1;
	temp = env->envp[index];
	env->envp[index] = ft_strdup(arg, flag);
	free(temp);
}


void    ft_export(t_env *env, char **argv, int index)
{
    int i;
    char **temp;
    int flag;

    i = 0;
    temp = NULL;
    flag = 0;
    if(!argv[index + 1])
    {
        ft_export_no_args_case(env);
        return ;
    }
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
        temp = malloc(sizeof(char *) * ft_count_elements(env->envp) + 1);
        i = 0;
        while(i < ft_count_elements(env->envp))
        {
            temp[i] = strdup(env->envp[i]);
            i++;
        }
        if(argv[index + 1][ft_find_variable_index(argv[index + 1]) + 1] == '\"')
            flag = 1;
        temp[i] = ft_strdup(argv[index + 1], flag);
        temp[i + 1] = NULL;
        ft_free(env->envp);
        env->envp = temp;
    }
}


int main(int argc, char **argv, char **envp)
{
    char *line;
    char **line_parser;
    t_env env;
    ft_get_env(&env, envp);
    while((line = readline("Minishell > ")) != 0)
    {
        if(ft_strcmp(line, "env") == 0)
            ft_env(&env);
        line_parser = ft_split(line ,' ');
        if(ft_strcmp(line_parser[0], "export") == 0)
        {
            ft_export(&env, line_parser, 0);
            //here
            ft_free(line_parser);
        } 
        free(line);
    }
    return (0);
}
