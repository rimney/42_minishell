/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 04:34:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/28 18:10:04 by rimney           ###   ########.fr       */
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

// void    ft_echo(t_env *env, char *str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         if(str[i] == ' ')
//             printf("DD\n");
//         if(str[i] == '\"' && str[i + 1] == '$')
//         {
//             printf("%s", &argv[index + 1][i + 1] + 1);
//             i += ft_expand(env, &argv[index + 1][i + 1]);
//         }
//         else if(argv[index + 1][i] == '$')
//            i += ft_expand(env, &argv[index + 1][i + 1]) + 1;
//         else if(argv[index + 1][i] == '\"')
//             i++;
//         printf("%c", str[i]);
//         i++;
//     }
//     printf("%s", argv[index + 1]);
//     printf("\n");
// }

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
       // printf("| %s |\n", str);
        if(ft_strncmp(env->envp[i], str, strlen(str)) == 0)
        {
            printf("%s", env->envp[i] + ft_find_variable_index(env->envp[i], '=') + 1);
            return (1);
        }
        i++;
    }
    return (0);
}

char    *ft_assign_echo(char *str)
{
    int i;
    int j;
    char *temp;

    i = 0;
    while(str[i] != ' ' && str[i])
        i++;
    temp = malloc(sizeof(char) * i + 1);
    j = 0;
    while(j < i)
    {
        temp[j] = str[j];
        j++;
    }
    temp[j] = 0;
    return (temp);
}

int ft_echo_single_q(char *str)
{
	int i;
	int flag;
	int	j;

	i = 0;
	flag = 0;
	while(str[i])
	{
		if(str[i] == '\'')
		{
			flag = 0;
			i += 1;
			j = i;
			while(str[j])
			{
				if(str[j] == '\'')
				{
					flag = 1;
					break;
        		}
				if(str[j + 1] == '\0' && flag == 0)
					return (0);
				j++;
			}
		}
		printf("%c", str[i++]);
	}
    return (i);
}

void    ft_echo(char *str, t_env *env)
{
    int i;
    char *temp;
    i = 0;
    while(str[i])
    {
		if(str[i] == '\'')
			i += ft_echo_single_q(&str[i]);
        if(str[i] == '$')
        {
            temp = ft_assign_echo(&str[i] + 1);
            ft_expand(env, temp);
            i += strlen(temp) + 1;
            free(temp);
        }
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
}

int main(int argc, char **argv, char **envp)
{
    t_env env;
    char *line;

    ft_get_env(&env, envp);
    while((line = readline("echo > ")))
    {
            ft_echo(line, &env);
        free(line);
    }
    
    return (0);
}