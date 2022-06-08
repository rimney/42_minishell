/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/08 04:33:28 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_simple_strjoin(char *s1, char *s2)
{
	int i;
	char *str;
	int j;

	i = 0;
	str = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 2);
	while(s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = ' ';
	j = 0;
	while(s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_count_tokens(t_token *token)
{
	int i;

	i = 0;
	while (token)
	{
		i++;
		token = token->next;
	}
	return (i);
}

void	ft_initialize_exec(t_exec *exec, char **envp, t_token *token, t_pipe *pipes)
{
	ft_get_env(&exec->env, envp);
	exec->args = ft_count_tokens(token);
	exec->append_count = 0;
	exec->heredoc_count = 0;
	exec->input_count = 0;
	exec->redirection_count = 0;
	exec->append_flag = 0;
	exec->input_flag = 0;
	exec->heredoc_flag = 0;
	exec->redirecion_flag = 0;
	exec->pipe_count = 0;
	exec->pipe_flag = 0;
	pipes->max = 1;
}

void	ft_fill_exec(t_exec *exec, t_token *token, char **envp, t_pipe *tpipe)
{
	int i = 0;
	int head_flag = 0;

	ft_initialize_exec(exec, envp, token, tpipe);
	exec->command = malloc(sizeof(char *) * ft_count_tokens(token) + 1);
	while(token)
	{
		if(token->type == WORD && head_flag == 0)
		{
			exec->command[i] = strdup(token->value);
			head_flag = 1;
		}
		else if(token->type == WORD && head_flag == 1)
			exec->command[i] = ft_simple_strjoin(exec->command[i], token->value);
		else if(token->type != WORD && head_flag)
		{
			i++;
			exec->command[i] = strdup(token->value);
			head_flag = 0;
			i++;		
		}
		token = token->next;
	}
	exec->command[i + 1] = 0;
}

void	print_list(t_token *token)
{
	while(token)
	{
		printf("<<< %s >>> ", token->value);
		token = token->next;
	}
	printf("\n");
}

void	ft_print_exec(t_exec *exec)
{
	int i;

	i = 0;
	while(exec->command[i])
	{
		printf("<< %s >> ", exec->command[i]);
		i++;
	}
	printf("\n");
}

int	is_token(char *str)
{
	if(ft_strcmp(str, "|") == 0)
		return (1);
	else
		return (0);
}



void ft_count_till_last_token(t_exec *exec, t_pipe *pipes)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (exec->command[i])
	{
		if(ft_strcmp(exec->command[i], "|") == 0)
		{
			exec->pipe_count += 2;
			pipes->max = 0;
		}
		else if(ft_strcmp(exec->command[i], ">") == 0)
			exec->redirection_count += 2;
		else if(ft_strcmp(exec->command[i], ">>") == 0)
			exec->append_count += 2;
		else if(ft_strcmp(exec->command[i], "<") == 0)
			exec->input_count += 2;
		else if(ft_strcmp(exec->command[i], "<<") == 0)
			exec->heredoc_count += 2;
	//	printf("%s\n", exec->command[i]);
		i++;
	}
	// if(exec->command[i + 1] || !exec->command[i - 1])
	// 	return (printf("error\n"), 0);
}


void	ft_mini_pipe(t_exec *exec, t_pipe *pipes)
{
//	int pid;
//	char **command_parser;
	int pipes_count = 0;

	ft_count_till_last_token(exec, pipes);
	printf("%d\n", exec->pipe_count);
		// printf("%d pipe_flag <<\n", exec->pipe_flag);

		ft_assign_tpipe(pipes, exec->pipe_count);
		execute_pipe(exec, 0, -1, pipes);
	printf("%d\n", pipes_count);
}

// void	ft_mini_output_redirection(t_exec *exec, t_pipe *pipes)
// {
// //	char **command_parser;
// 	int redirection_count;

// 	pipes->max = 0;
// 	redirection_count = ft_count_till_last_token(exec, ">");
// 	ft_redirect(redirection_count, exec, pipes);
// }

void	ft_assign_tpipe(t_pipe *pipe, int argc)
{
	pipe->fd[0] = -1;
	pipe->fd[1] = -1;
	pipe->in_save = -1;
	pipe->in = -1;
	pipe->max = argc;
}

int only_pipe_flag(t_exec *exec)
{
	int i;

	i = 0;
	//ft_count_till_last_token(exec, pipes);
	if(exec->pipe_count > 0 && exec->input_count == 0 && exec->append_count == 0
		&& exec->heredoc_count == 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}

int	ft_mini_redirect_output(t_exec *exec, t_pipe *tpipe, int index)
{
	int i;
	int command_location;

	command_location = 0;
	i = index;
	if(ft_strcmp(exec->command[i], ">") == 0)
	{
			command_location = i - 1;
			i += ft_redirect(i, exec, tpipe, command_location);
			i--;
	}
	if(ft_strcmp(exec->command[i], "|") == 0)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count + 1);
		execute_pipe(exec, i + 1, -1, tpipe);
		i += tpipe->max;
	}
	printf("%s\n", exec->command[i - 2]); // should base on this one tomorrow 
	return(i - 1);
}

void	ft_minishell(t_exec *exec, t_pipe *tpipe)
{
	int i;
	int command_location;

	i = 0;
	command_location = 0;
	ft_count_till_last_token(exec, tpipe);
	// if(only_pipe_flag(exec) && exec->args > 2)
	// {
	// 	// ft_assign_tpipe(tpipe, exec->pipe_count + 1);
	// 	// printf("%d\n", tpipe->max);
	// 	// execute_pipe(exec, 0, -1, tpipe);
	// 	// i += exec->pipe_count + 1;
	// 	// printf("%d << \n", i);
	// }
	while(exec->command[i + 1] != NULL && i < exec->args)
	{
		if(ft_strcmp(exec->command[i], ">") == 0)
			i += ft_mini_redirect_output(exec, tpipe, i);
		else
			printf("dodo\n");
		//printf("%s\n", exec->command[i - 1]);
		// if(exec->command[i] && ft_strcmp(exec->command[i], "|") == 0)
		// {
		// printf("%d\n", i);
		// ft_assign_tpipe(tpipe, exec->pipe_count);
		// execute_pipe(exec, i + 1, -1, tpipe);
	 	// i += exec->pipe_count;
		// printf("%d\n", i);
		// }
				//  command_location = i - 1;
				//  i += ft_redirect(i, exec, tpipe, command_location);
				//  i--;
		// //	printf("%d << before\n", i);
		// 	if(exec->command[i] && ft_strcmp(exec->command[i], "|") == 0)
		// 	{
		// 		ft_assign_tpipe(tpipe, exec->pipe_count + 1);
		// 		execute_pipe(exec, i + 1, -1, tpipe);
		// 	 	i += exec->pipe_count;
		// 		//printf("%d << \n", i);
		// 	}
		i++;
	}
}

// 	// 	else
// 	// 		printf("www\n");
// 	// 	i++;
// 	// 	}
// 	//printf("%s\n", exec->command[0]);
// 	//tpipe->fd[0] = 0;
// }



int	main(int argc, char **argv, char **envp)
{
	char	*line;
	int		i ;
	t_token	*lst;
	t_redir	*redir;
	t_exec exec;
	t_pipe pipes;
	i = 0;
	redir = NULL;
	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			printf(GREEN_COLOR);
			line = readline("BomusShell$>\033[0;37m");
			if (line == NULL)
				exit(0);
			if (line[0] == '\0')
				return (0);
			add_history(line);
			lst = token_split(line, ' ');
			redir = parser(lst, line);
			//printf("here\n");
			ft_fill_exec(&exec, lst, envp, &pipes);
			
		//	ft_print_exec(&exec);
			ft_assign_tpipe(&pipes, 3);
			ft_initialize_exec(&exec,envp, lst, &pipes);
		//	ft_mini_pipe(&exec, &pipes);
			ft_minishell(&exec, &pipes);
			wait(NULL);
			// printf("\nTOKEN LIST\n\n");
			//print_lst(lst);
			// printf("\nREDIR LIST\n\n");
			//print_redir(redir);
			//ft_free(exec.command);
		}
	}
	return (0);
}
