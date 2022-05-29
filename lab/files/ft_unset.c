/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 04:22:04 by rimney            #+#    #+#             */
/*   Updated: 2022/05/29 08:20:18 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void    ft_free(char **str)
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

char **ft_copy_temp_envp(char **temp, t_env *env, int unset)
{
    int i;
    int j;

    j = 0;
    i = 0;    
    temp = malloc(sizeof(char *) * ft_count_elements(env->envp));
    printf("%d E\n", ft_count_elements(env->envp));
    while(i < ft_count_elements(env->envp))
    {
        if(i == unset)
            j++;
        temp[j] = strdup(env->envp[i]);
        i++;
        j++;
    }
    temp[j] = 0;
    return (temp);
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

int ft_count_elements(char **str)
{
  int i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

void    ft_unset(char *str, t_env *env)
{
    int i;
    int unset;
    char **temp;
    int j;

    i = 0;
    unset = 0;
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
        temp = malloc(sizeof(char *) * ft_count_elements(env->envp) + 1);
        while(i < ft_count_elements(env->envp))
        { 
            if(j == unset)
                i++;
            temp[j] = strdup(env->envp[i]);
            i++;
            j++;
        }
        temp[j] = 0;
    }
    ft_free(env->envp);
    env->envp = temp;
}

int main(int argc, char **argv, char **envp)
{
    char *line;
    t_env env;
    char **line_parser;

    ft_get_env(&env, envp);

    while((line = readline("unset >")))
    {
        line_parser = ft_split(line, ' ');
        if(ft_strcmp(line, "env") == 0)
            ft_env(&env);
        if(ft_strcmp(line_parser[0], "unset") == 0)
            ft_unset(line_parser[1], &env);
        free(line);
    }
    
}