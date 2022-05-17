/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:38:09 by rimney            #+#    #+#             */
/*   Updated: 2022/05/17 01:47:51 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_count_elements(char **str)
{
  int i;

  i = 0;
  while(str[i])
    i++;
  return (i);
}

int main(int argc, char **argv, char **envp)
{
  char *line;
  char **line_parser;
  int pid;

  while(1)
  {
    line = readline("Minishell >> ");
    line_parser = ft_split(line, ' ');
    pid = fork();
    if (pid == 0)
      ft_pipe(ft_count_elements(line_parser), line_parser, envp);
    waitpid(pid, 0, 0);
  }
  return (0);
}
