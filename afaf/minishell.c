/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/05 04:52:43 by rimney           ###   ########.fr       */
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
	while (i < exec->args)
	{
		if(ft_strcmp(exec->command[i], "|") == 0)
		{
			exec->pipe_count += 2;
			pipes->max += 2;
		}
		else if(ft_strcmp(exec->command[i], ">") == 0)
			exec->redirection_count += 2;
		else if(ft_strcmp(exec->command[i], ">>") == 0)
			exec->append_count += 2;
		else if(ft_strcmp(exec->command[i], "<") == 0)
			exec->input_count += 2;
		else if(ft_strcmp(exec->command[i], "<<") == 0)
			exec->heredoc_count += 2;
		i++;
	}
	// if(exec->command[i + 1] || !exec->command[i - 1])
	// 	return (printf("error\n"), 0);
}


// void	ft_mini_pipe(t_exec *exec, t_pipe *pipes)
// {
// //	int pid;
// //	char **command_parser;
// 	int pipes_count;

// 	pipes_count = 0;
// 	if(pipes_count == 0)
// 	{
// 		printf("%s\n", exec->command[0]);
// 		ft_execute_command(exec, 0);

// 	}
// 	else if(pipes_count > 0)
// 	{
// 		// printf("%d pipe_flag <<\n", exec->pipe_flag);

// 		ft_assign_tpipe(pipes, pipes_count, exec->env.envp);
// 		execute_pipe(exec, 0, -1, pipes);
// 	}
// }

// void	ft_mini_output_redirection(t_exec *exec, t_pipe *pipes)
// {
// //	char **command_parser;
// 	int redirection_count;

// 	pipes->max = 0;
// 	redirection_count = ft_count_till_last_token(exec, ">");
// 	ft_redirect(redirection_count, exec, pipes);
// }


void	ft_minishell(t_exec *exec, t_pipe *tpipe)
{
	int i;
	//int fd;

	i = 0;
	ft_count_till_last_token(exec, tpipe);
	// while(exec->command[i])
	// {
	// 	printf("%s\n", exec->command[i]);
	// 	// if(ft_strcmp(exec->command[i], ">") == 0)
	// 	// {
	// 	// 	//printf("%d <<\n", exec->redirection_count);
	// 	// 	printf("%s\n", exec->command[0]);
	// 	// //	ft_redirect(i,  exec, tpipe);
	// 	// }
	// 	i++;
	// }
	printf("%s\n", exec->command[0]);
	tpipe->fd[0] = 0;
}

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
		//ft_mini_pipe(&exec, &pipes);
			ft_minishell(&exec, &pipes);
			ft_initialize_exec(&exec,envp, lst, &pipes);
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
