/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/18 02:34:04 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
int ft_is_another_flag(t_exec *exec, int index);
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
	exec->sev_flag = 0;
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
	exec->initial_flag = 0;
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
int	ft_count_till_other_token(t_exec *exec, int index, char *token)
{
	int i;
	int count;

	count = 0;
	i = index;
	while(exec->command[i])
	{
		if(ft_strcmp(exec->command[i], token) == 0)
			count += 2;
		else
			return count;
		i += 2;
	}
	return (count);
}


int	ft_mini_pipe(t_exec *exec, t_pipe *pipes, int in, int count, int index)
{

	int i;

	i = index;
	count++;
	// if(exec->command[i + exec->pipe_count])
	// {
	// //	printf("%s <<<<<<<<<heere\n", exec->command[i + exec->pipe_count]);
	// 	if(ft_strcmp(exec->command[i + exec->pipe_count], ">") == 0)
	// 	{
	// 		exec->redirecion_flag = 1;
	// 		exec->pipe_count += 1;
	// 	}
	// 	if(ft_strcmp(exec->command[i + exec->pipe_count], ">>") == 0)
	// 		exec->append_flag = 1;
	// 	if(ft_strcmp(exec->command[i + exec->pipe_count], "<") == 0)
	// 		exec->input_flag = 1;
	// }
	in = open(exec->command[index - 1], O_RDONLY);
	ft_assign_tpipe(pipes, exec->pipe_count + i - 1);
	
	execute_pipe(exec, i + 1, in, pipes);
//	i += exec->pipe_count + 2;
	//printf("%s <<\n", exec->command[index + 1]);
	exec->append_flag = 0;
	//exec->redirection_count = 0;
	return i;
	//printf("%d >> append << \n", exec->append_count);
	//exec->redirection_count = ft_count_till_other_token(exec, i, ">");
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

int only_command_flag(t_exec *exec)
{
	//ft_count_till_last_token(exec, pipes);
	if(exec->pipe_count == 0 && exec->input_count == 0 && exec->append_count == 0
		&& exec->heredoc_count == 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}

int only_output_redirection_flag(t_exec *exec)
{
	if(exec->pipe_count == 0 && exec->input_count == 0 && exec->append_count == 0
		&& exec->heredoc_count == 0 && exec->redirection_count > 0 && exec->args > 0)
			return (1);
	return (-1);
}

int only_heredoc_flag(t_exec *exec)
{
	if(exec->pipe_count == 0 && exec->input_count == 0 && exec->append_count == 0
		&& exec->heredoc_count > 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}

int only_append_flag(t_exec *exec)
{
	if(exec->pipe_count == 0 && exec->input_count == 0 && exec->append_count > 0
		&& exec->heredoc_count == 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}

int only_input_flag(t_exec *exec)
{
	if(exec->pipe_count == 0 && exec->input_count > 0 && exec->append_count == 0
		&& exec->heredoc_count == 0 && exec->redirection_count == 0 && exec->args > 0)
			return (1);
	return (-1);
}

// int	after_

// int	ft_apply_pipe_after_redirection(int fd, t_exec *exec, t_pipe *tpipe, int index, int count)
// {
// 	fd = open(exec->command[count], O_RDONLY);
// 	ft_assign_tpipe(tpipe, exec->pipe_count + (count - 1));
// 	execute_pipe(exec, index + 1, fd, tpipe);
// 	return (1);
// }




int	ft_mini_redirect_output(t_exec *exec, t_pipe *tpipe, int index)
{
	int i;
	int command_location;
	int fd;

	command_location = 0;
	i = index;
	fd = -1;
	exec->redirection_count = ft_count_till_other_token(exec, 1, ">");
	if(ft_strcmp(exec->command[i], ">") == 0)
	{
		command_location = i - 1;
		ft_redirect(i, exec, command_location);
			i += exec->redirection_count;
	}
	if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
	{
		ft_mini_pipe(exec, tpipe, fd, exec->redirection_count, i);
		i += exec->pipe_count + exec->redirection_count;
	}
	if(exec->command[i] && ft_is_another_flag(exec, i) == HEREDOC)
	{
		ft_execute_heredoc(exec, tpipe, i);
		 i += exec->heredoc_count;
	}
	if(exec->command[i] && ft_is_another_flag(exec, i) == HEREDOC)
	{
		ft_execute_heredoc(exec, tpipe, i);
		 i += exec->heredoc_count;
	}
	if(exec->command[i] && ft_is_another_flag(exec, i) == REDIRIN)
	{
		ft_redirect_input(exec, tpipe, i, 1);
		 i += exec->redirection_count;
	}
	
	return(i);
}

int ft_is_another_flag(t_exec *exec, int index)
{
	if(ft_strcmp(exec->command[index], ">>") == 0)
		return(APPEND);
	else if(ft_strcmp(exec->command[index], "|") == 0)
		return(PIPE);
	else if(ft_strcmp(exec->command[index], ">") == 0)
		return(REDIROUT);
	else if(ft_strcmp(exec->command[index], "<") == 0)
		return(REDIRIN);
	else if(ft_strcmp(exec->command[index], "<<") == 0)
		return(HEREDOC);
	return (0);
}


// void	ft_mini_redirect_output_7Flag(t_exec *exec, int fd, int index)
// {
// 	int fd2;

// 	// if(ft_strcmp(exec->command[exec->pipe_count], ">") == 0)
// 	fd2 = open(exec->command[exec->pipe_count], O_RDONLY);
// 	 	fd = open(exec->command[index + exec->pipe_count + 1], O_RDWR, O_TRUNC , 0644);
// 	// 	if(ft_strcmp(exec->command[exec->pipe_count], ">>") == 0)
// 	// dup2(fd2, 0);
// 	// close(fd2);
// 	dup2(fd, 1);
// 	close(fd);
// 		ft_execute_command(exec, index + 1);
// }

int	ft_mini_append(t_exec *exec, t_pipe *tpipe, int i)
{
	int fd;
//	int pid;

	fd = -1;
	
	exec->append_count = ft_count_till_other_token(exec, 1, ">>");
	exec->pipe_count = 0;
	while(exec->command[i + 1] != NULL)
	{
		if(ft_strcmp(exec->command[i], ">>") == 0)
		{
		//	printf("bbb\n");
			ft_append(i, exec, tpipe, 0);
			i += exec->append_count;
		}
		// if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE && exec->command[i + 2] && ft_is_another_flag(exec, i + 2) == REDIROUT) 
		// {
		// 	printf("rediout\n");
		// 	i += 2;
		// 	printf("%s << exec\n", exec->command[i]);
		// }
		if(exec->command[i] && ft_is_another_flag(exec, i) == PIPE)
		{
			exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			exec->redirection_count = ft_count_till_other_token(exec, i + exec->pipe_count, ">");
			if(exec->command[i + 2] && ft_is_another_flag(exec, i + 2) == REDIROUT)
			{
			//	printf("%d >> exec->\n", exec->redirection_count);
				i += 4;
				//printf("%s <<<<<\n", exec->command[i]);
				exec->pipe_count = ft_count_till_other_token(exec, i, "|");
			}
			if((exec->command[i + 2] && ft_is_another_flag(exec, i + 2) != REDIROUT) || exec->command[i + 2] == NULL)
			{
				printf("%d >>>> pipe coumt\n", exec->pipe_count);
				ft_mini_pipe(exec, tpipe, fd, i - 1, i);
				i += exec->pipe_count;
			}
			//printf("%s <<<< \n", exec->command[i]);
	//		printf("%d >> index\n", i);
			
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == HEREDOC)
		{
			ft_execute_heredoc(exec, tpipe, i);
			 i += exec->heredoc_count - 1;
		}
		if(exec->command[i] && ft_is_another_flag(exec, i) == REDIRIN)
		{
			ft_redirect_input(exec, tpipe, i, 1);
			 i += exec->redirection_count;
		}
		
			i++;
	}
	return(i);
}

int	ft_execute_only_flag(t_exec *exec, t_pipe *tpipe)
{
	int pid;

	if(only_command_flag(exec) > 0)
	{
		pid = fork();
		if(pid == 0)
			ft_execute_command(exec, 0);
	}
	else if(only_pipe_flag(exec) > 0 && exec->args > 2)
	{
		ft_assign_tpipe(tpipe, exec->pipe_count);
		execute_pipe(exec, 0, -1, tpipe);
		wait(NULL);
	}
	else if(only_output_redirection_flag(exec) > 0)
		ft_mini_redirect_output(exec, tpipe, 1);
	else if(only_heredoc_flag(exec) > 0)
		ft_execute_heredoc(exec, tpipe, 0);
	else if(only_append_flag(exec) > 0)
		ft_mini_append(exec, tpipe, 1);
	else if(only_input_flag(exec) > 0)
		ft_redirect_input(exec, tpipe, 0, 0);
	else
		return (0);
	return(1);
}

void	ft_minishell(t_exec *exec, t_pipe *tpipe)
{
	int i;
	int command_location;
	//int pid;

	i = 0;
	command_location = 0;
	ft_count_till_last_token(exec, tpipe);

	if(ft_execute_only_flag(exec, tpipe))
		return ;
	else
	{
		while(exec->command[i + 1] != NULL)
		{
			if(ft_strcmp(exec->command[i], ">") == 0 && exec->redirecion_flag == 0 && exec->initial_flag == 0)
			{
	//			printf("bobo\n");
					ft_mini_redirect_output(exec, tpipe, i);
					i += exec->redirection_count;
			}
			if(ft_strcmp(exec->command[i], ">>") == 0 && exec->initial_flag == 0)
			{
				exec->initial_flag = 1;
				ft_mini_append(exec, tpipe, i);
				printf("%d << redi\n", exec->redirection_count);
				printf("minimini\n");
				i += exec->append_count;
			}
		// else
		// 	printf("dodo\n");
		//printf("%s\n", exec->command[i - 1]);

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
		wait(NULL);
		i++;
		}
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
		//	ft_assign_tpipe(&pipes, 3);
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
