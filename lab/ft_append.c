/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:30:30 by rimney            #+#    #+#             */
/*   Updated: 2022/04/17 02:29:13 by rimney           ###   ########.fr       */
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

void	*ft_locate_env(char **env)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	str = ft_split(env[i] + 5, ':');
	return (str);
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

char	*ft_check_command(char **env, char *command)
{
	int		i;
	char	*cmd;


	i = 0;
	cmd = ft_filter_command(command);
	while (env[i])
	{
		env[i] = ft_strjoin(env[i], "/");
		free(env[i]);
		env[i] = ft_strjoin(env[i], cmd);
		if (access(env[i], F_OK) == 0)
		{
			if (!ft_is_space(command))
				free(cmd);
			return (env[i]);
		}
		free(env[i]);
		i++;
	}
    return (0);
}

int main(int argc, char **argv, char **envp)
{

    printf("%s\n", ft_check_command(ft_locate_env(envp), argv[1]));
    system("leaks a.out");
    return (0);
}