/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:30:30 by rimney            #+#    #+#             */
/*   Updated: 2022/04/28 19:56:59 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../minishell.h"

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
	{
		i++;
	}
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

char	*ft_is_a_command(char **env, char *command)
{
	int		i;
	char	*cmd;

	i = 0;
	cmd = ft_filter_command(command);
	if(access(command, F_OK) == 0)
		return (command);
	while (env[i])
	{
		free(env[i]);
		env[i] = ft_strjoin(env[i], "/");
		free(env[i]);
		env[i] = ft_strjoin(env[i], cmd);
		if (access(env[i], F_OK) == 0)
		{
			if (!ft_is_space(command))
				free(cmd);
			return (env[i]);
		}
		i++;
	}
    return (0);
}

void	ft_free(char **value)
{
	int i;

	i = 0;
	while (value[i])
	{
		free(value[i]);
		i++;
	}
	free(value);
}

char	*ft_exec_command(char *command, char **envp, char **argv)
{
	int i;
	char **str;
	char **cmd_parser;
	char *ret;

	i = 0;
	cmd_parser = ft_split(command, ' ');
	str = ft_split(ft_locate_env(envp), ':');
	ret = ft_is_a_command(str, command);
	ft_free(str);
	ft_free(cmd_parser);
	return (ret);
}

int main(int argc, char **argv, char **envp)
{
	printf("%s\n", ft_exec_command(argv[1], envp, argv));
  //  system("leaks append");
    return (0);
}