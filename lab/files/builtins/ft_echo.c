/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 04:34:26 by rimney            #+#    #+#             */
/*   Updated: 2022/05/31 06:32:29 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
    int len;


    i = 0;
    skipper = 0;
     while(str[skipper] != ' ' && str[skipper])
         skipper++;
    printf("%s\n", str);
    while(env->envp[i])
    {
        if(ft_strncmp(env->envp[i], str, strlen(str) - 1) == 0)
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

// int ft_echo_single_q(char *str)
// {
// 	int i;
// 	int flag;
// 	int	j;

// 	i = 0;
// 	flag = 0;
// 	while(str[i] && flag == 0)
// 	{
// 		if(str[i] == '\'')
// 		{
// 			flag = 0;
// 			i += 1;
// 			j = i;
// 			while(str[j])
// 			{
// 				if(str[j] == '\'')
// 				{
// 					flag = 1;
// 					break;
//         		}
// 				if(str[j + 1] == '\0' && flag == 0)
// 					return (0);
// 				j++;
// 			}
// 		}
//         // if(str[i] != '\'')
//         //     printf("%c", str[i]);
//         i++;
// 		printf("%c", str[i++]);
// 	}
//         printf(" || %d || \n", i);
//     return (i);
// }

// int	ft_echo_double_q(char *str)
// {
// 	int i;
// 	int flag;

//     i = 0;
    
	
// }

int ft_find_next_index(char *str, char c)
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


int ft_handle_single_quotes(char *str)
{
  int i;
  int index;
  
  i = 0;
  while(str[i])
  {
    if(str[i] == '\'')
    {
      i++;
      index = ft_find_next_index(&str[i], '\'');
      if(!index)
        return 0;
      while(i <= index)
      {
        printf("%c", str[i]);
        i++;
      }
    }
      else
         printf("%c", str[i]);
        if(str[i] == '\'')
            return (i);
      i++;
  }
  return i + 1;
}

int ft_handle_double_quotes(char *str, t_env *env)
{
  int i;
  int index;

  i = 0;
  while(str[i])
  {
    if(str[i] == '\"')
    {
      i++;
      index = ft_find_next_index(&str[i], '\"');

      while(i <= index)
      {
        if(str[i] == '$')
        {
            ft_expand(env, &str[i]);
        }
        else
          printf("%c", str[i]);
      i++;   
      }
    }
      else
        printf("%c", str[i]);
        i++;
  }
  return (i);
}



void    ft_echo(char *str, t_env *env)
{
    int i;
    char *temp;
    int flag;

    i = 0;
    while(str[i])
    {
       if(str[i] == '$')
        {
            temp = ft_assign_echo(&str[i] + 1);
            ft_expand(env, temp);
            i += strlen(temp) + 1;
            free(temp);
        }
        else if(str[i] == '\'')
            i += ft_handle_single_quotes(str);
        else if(str[i] == '\"')
            i += ft_handle_double_quotes(str, env);
        printf("%c", str[i]);
        i++;
    }
    printf("\n");
}



// int main(int argc, char **argv, char **envp)
// {
//     t_env env;
//     char *line;

//     ft_get_env(&env, envp);
//     while((line = readline("echo > ")))
//     {
//             ft_echo(line, &env);
//         free(line);
//     }
    
//     return (0);
// }