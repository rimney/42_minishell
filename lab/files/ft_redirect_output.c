/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 04:04:08 by rimney            #+#    #+#             */
/*   Updated: 2022/05/18 01:57:39 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_single_redirect(int argc, char **argv)
{
	int fd;
	char *line;
	if(argc == 3 && ft_strcmp(argv[1], ">") == 0)
	{
		fd = open(argv[2], O_CREAT | O_RDWR, 0644);
		while(1)
		{
			fd = open(argv[2], O_RDWR | O_APPEND, 0644);
			line = readline("");
			write(fd, line, strlen(line));
			write(fd, "\n", 1);
			free(line);
		}
	}
}

// void	ft_free(char **value)
// {
// 	int i;

// 	i = 0;
// 	while (value[i])
// 	{
// 		free(value[i]);
// 		i++;
// 	}
// 	free(value);
// }


void	ft_advanced_redirect(int argc, char **argv, char **envp, int i)
{
	int	fd;
	char **cmd_parser;

	cmd_parser = ft_split(argv[0], ' ');
	fd = open(argv[i + 1], O_CREAT | O_RDWR | O_TRUNC , 0644);
	dup2(fd, STDOUT_FILENO);
	execve(ft_exec_command(argv[0], envp, argv), cmd_parser, envp);
	close(fd);
}

int	ft_redirect(int argc, char **argv, char **envp)
{
	int fd;
	char *line;
	int i = 1;
	int pid;

	if(argc == 1 && ft_strcmp(argv[0], ">") == 0)
		ft_single_redirect(argc, argv);
	else
	{
			while(i < argc)
			{
				if(ft_strcmp(argv[i], ">") == 0)
				{
					pid = fork();
					if(pid == 0)
						ft_advanced_redirect(argc, argv, envp, i);
				}
				i++;
		//	printf("%d <<\n", i);
			waitpid(pid, 0, 0);
			}
	}
	return (0);
}

// int	ft_count_elements(char **str)
// {
// 	int i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

int main(int argc, char **argv, char **envp)
{
  char *line;
  char **line_parser;
  int pid;
  char *history;

  while((line = readline("Minishell >> ")))
  {
	printf("dd\n");
    add_history(line);
    line_parser = ft_split(line, ' ');
    if(ft_strcmp(line, "history") == 0)
      printf("h\n");
    else
    {
      pid = fork();
      if (pid == 0)
        ft_redirect(ft_count_elements(line_parser), line_parser, envp);
      ft_free(line_parser);
      free(line);
      waitpid(pid, 0, 0);
    }
  }
  return (0);
}
