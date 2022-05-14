/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:38:09 by rimney            #+#    #+#             */
/*   Updated: 2022/05/14 04:00:55 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int spawn_proc (int in, int out, struct command *cmd)
{
  pid_t pid;

  if ((pid = fork ()) == 0)
    {
      if (in != 0)
        {
          dup2 (in, 0);
          close (in);
        }

      if (out != 1)
        {
          dup2 (out, 1);
          close (out);
        }

      return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }

  return pid;
}

int
fork_pipes (int n, struct command *cmd)
{
  int i;
  pid_t pid;
  int in, fd [2];
  in = 0;

  for (i = 0; i < n - 1; ++i)
    {
      pipe (fd);

      spawn_proc (in, fd [1], cmd + i);

      close (fd [1]);

      in = fd [0];
    } 
  if (in != 0)
    dup2 (in, 0);
  return execvp (cmd [i].argv [0], (char * const *)cmd [i].argv);
}

int main (int argc, char **argv)
{
  const char *ls[] = { "ls", "-l", 0 };
  const char *awk[] = { "wc", "-l", 0 };
  const char *sort[] = { "sort", 0 };
  const char *uniq[] = { "uniq", 0 };

  struct command cmd [] = { {ls}, {awk}, {sort}, {uniq} };

  return fork_pipes (4, cmd);
}