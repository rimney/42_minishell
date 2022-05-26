/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 04:34:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/26 22:20:04 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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


int    ft_expand(t_env *env, char *str)
{
    int i;
    int skipper;

    i = 0;
    skipper = 0;
     while(str[skipper] != ' ' && str[skipper])
         skipper++;
    while(env->envp[i])
    {
        if(ft_strncmp(env->envp[i], str, strlen(str)) == 0)
        {
            printf("%s", env->envp[i] + ft_find_variable_index(env->envp[i], '=') + 1);
            break ;
        }
        i++;
    }
    return (skipper);
}

int ft_count_elements(char **str)
{
  int i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

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

void    ft_echo(t_env *env, char **argv, int index)
{
    int i;

    i = 0;
    while (argv[index + 1][i])
    {
        if(argv[index + 1][i] == ' ')
            printf("DD\n");
        if(argv[index + 1][i] == '\"' && argv[index + 1][i + 1] == '$')
        {
            printf("%s", &argv[index + 1][i + 1] + 1);
            i += ft_expand(env, &argv[index + 1][i + 1]);
        }
        else if(argv[index + 1][i] == '$')
           i += ft_expand(env, &argv[index + 1][i + 1]) + 1;
        else if(argv[index + 1][i] == '\"')
            i++;
        printf("%c", argv[index + 1][i]);
        i++;
    }
    printf("%s", argv[index + 1]);
    printf("\n");
}

int main(int argc, char **argv, char **envp)
{
    t_env env;
    char *line;
    char **line_parser;

    ft_get_env(&env, envp);
    while((line = readline("expand > ")))
    {
        line_parser = ft_split(line, ' ');
        if(ft_strcmp(line, "echo"))
            ft_echo(&env, line_parser[], 0);
        free(line);
    }
    
    return (0);
}