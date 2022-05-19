/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 00:30:30 by rimney            #+#    #+#             */
/*   Updated: 2022/05/19 03:54:41 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "../../minishell.h"





// int ft_exec_heredoc(char **argv, char **envp, int index, int flag)
// {
//     char *delimiter;
//     char *line;
// 	char **command_2D;

//     delimiter = strdup(argv[index + 1]);
//     printf("Here we go: %s\n", delimiter);
//     while(1)
//     {
//         line = readline("hereddoc> ");
//         if(ft_strcmp(line, delimiter) == 0)
//         {
// 			command_2D = ft_split(argv[index - 1], ' ');
// 			if(flag)
//             execve(ft_exec_command(argv[index - 2], envp, argv), command_2D, envp);
// 			else
//           	  execve(ft_exec_command(argv[index - 1], envp, argv), command_2D, envp);
//             return (1);
//         }
//         free(line);
//     }
//     return(0); 
// }

// int ft_heredoc(int argc, char **argv, char **envp)
// {
// 	int i = 1;
// 	int flag;

// 	while(i < argc)
// 	{
// 		if(ft_exec_command(argv[i], envp, argv) && ft_exec_command(argv[i + 1], envp, argv))
// 		{
// 			printf("Yes\n");
// 			flag = 1;
// 			i++;
// 		}	
// 		else if(ft_strcmp(argv[i],  "<<") == 0)
// 			ft_exec_heredoc(argv, envp, i, 0);
// 		i++;
// 	}
		
// 	return (0);
// }

void	ft_easy_heredoc(char **argv, char *delimiter)
{
	int i;
	char	**lines_holder;
	char	*line;

	i = 0;
	int j = 0;
	while(line != delimiter)
	{
		line = readline("R>heredoc> ");
		lines_holder[i] = strdup(line);
		i++;
		if(ft_strcmp(line, delimiter) == 0)
		{
			while(j < i - 1)
				printf("%s\n", lines_holder[j++]);
			return ;
		}
		else
			free(line);
	}
}

void	ft_advanced_heredoc(int argc, char **argv, char **envp, int index)
{
	char *delimiter;

	delimiter = strdup(argv[index + 1]);
	printf("frlimiter >%s\n", delimiter);
	free(delimiter);
	return ;

}

void	ft_heredoc(int argc, char **argv, char **envp)
{
	int i = 1;
	char *delimiter = NULL;
	int pid;

	if(argc == 3 && ft_strcmp(argv[1], "<<") == 0)
	{
		delimiter = strdup(argv[2]);
		ft_easy_heredoc(argv, delimiter);
		free(delimiter);
		return ;
	}
	else
	{
		while(i < argc)
		{
			if(ft_strcmp(argv[i], "<<") == 0)
				ft_advanced_heredoc(argc, argv, envp, i);
			i++;
		}
	}
}
