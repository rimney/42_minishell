/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 04:47:20 by rimney            #+#    #+#             */
/*   Updated: 2022/05/31 07:53:38 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char *history;

// int ft_count_elements(char **str)
// {
//   int i;

//   i = 0;
//   while(str[i])
//     i++;
//   return (i);
// }

typedef struct s_pipe
{
	int fd[2];
	int in;
	int max;
	int in_save;
	t_env *env;
} t_pipe;

void	ft_assign_tpipe(t_pipe *pipe, int argc)
{
	pipe->fd[0] = -1;
	pipe->fd[1] = -1;
	pipe->in_save = -1;
	pipe->in = -1;
	pipe->max = argc;
}

void	ft_pipe(int in, t_pipe *tpipe ,char **command, char **envp)
{
        if  (in != -1)
        {
            dup2(in , 0);    
            close(in);
        }
        if (tpipe->fd[1] != -1)
        {
            dup2(tpipe->fd[1] , 1);
            close(tpipe->fd[1]);
        }
        close(tpipe->fd[0]);
        if(execve(command[0],command , envp) == -1)
		{
			printf("command not found\n");
			exit(0);
		}
}



int exuecute_pipe(char **args, int index, int in,  t_pipe *tpipe, char **envp)
{
	int in_save;
	in_save = -1;
	int pid;
	
	char *command[2];

    if (index >= tpipe->max)
        return 0;       
    if (args[index + 1] != NULL)
    {
        pipe(tpipe->fd);
        in_save =  tpipe->fd[0];
    }
    pid = fork();
    if (pid == 0)
    {
    	command[0] = ft_exec_command(envp , args[index]);
    	command[1] = NULL;
		ft_pipe(in, tpipe, command, envp);
		exit(0);
    }
    if (in != -1)
        close(in);
    if (tpipe->fd[1] !=  -1)
        close(tpipe->fd[1]);
  	exuecute_pipe(args ,  index + 2, in_save , tpipe, envp);
    waitpid(pid , 0 , 0);
     return 0;

}
void	ft_test(t_pipe *pipe)
{
	printf("%d\n", pipe->fd[0]);
	printf("%d\n", pipe->fd[1]);
	printf("%d\n", pipe->in);
	//printf("%d\n", pipe->out);
	printf("%d\n", pipe->in_save);
}


int main(int argc, char **argv, char **envp)
{
	char *line;
	char **line_parser;
	t_env env;
	t_pipe pipe;

	ft_get_env(&env, envp);
	line = readline("Minishell >>");
	line_parser = ft_split(line, ' ');
	ft_assign_tpipe(&pipe, ft_count_elements(line_parser)); // should be replaced with npipes;
	while((line = readline("Minishell >> ")))
	{
		add_history(line);
    	line_parser = ft_split(line, ' ');
		pipe.max = ft_count_elements(line_parser);
	    exuecute_pipe(line_parser, 0, -1, &pipe, envp);
        waitpid(-1 , 0 , 0);
  		free(line);
  	}
  	return (0);
}
