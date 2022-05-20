/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 23:32:39 by rimney            #+#    #+#             */
/*   Updated: 2022/05/20 03:21:42 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_locate_env(char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	return (env[i]);
}

char	*ft_filter_command(char *command)
{
	char	*ret;
	int		i;

	i = 0;
	if (ft_is_space(command))
		return (command);
	while (command[i] && command[i] != ' ')
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (command[i] != ' ')
	{
		ret[i] = command[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	ft_free(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*ft_exec_command(char **envp, char *command)
{
	int		i;
	char	*ret;
	char	**env;
	char	**temp;

	i = 0;
	temp = ft_split(ft_locate_env(envp) + 5, ':');
	env = malloc(sizeof(char *) * 9);
	while(temp[i])
	{
		env[i] = ft_strjoin(temp[i], "/", command);
		i++;
	}
	ft_free(temp);
	i = 0;
	while (env[i])
	{
		if (access(env[i], F_OK) == 0)
		{
			ret = strdup(env[i]);
			//ft_free(env);
			return (ret);
		}
		i++;
	}
//	ft_free(env);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
//     char *str;

//     str = ft_check_command(envp, argv[1]);
//     printf("%s |\n", str);
// 	system("leaks a.out");
//     return (0);
// }