/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:07:32 by atarchou          #+#    #+#             */
/*   Updated: 2022/06/01 16:52:47 by rimney           ###   ########.fr       */
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

void	ft_fill_exec(t_exec *exec, t_token *token)
{
	int i = 0;
	int head_flag = 0;
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

int ft_count_till_last_pipe(t_exec *exec)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (exec->command[i])
	{
		if(ft_strcmp(exec->command[i], "|") == 0)
			count += 2;
		i++;
	}
	if(ft_strcmp(exec->command[i - 1],  "|") == 0 || !exec->command[i - 1])
		return (printf("error\n"), 0);
	return (count + 1);
}


void	ft_mini(t_exec *exec, char **envp, t_pipe *pipes)
{
	int i;
	//int pid;
	//char **command_parser;
	int pipes_count;
	i = 0;
	while(exec->command[i])
	{
		if(is_token(exec->command[i]))
		{
			pipes_count = ft_count_till_last_pipe(exec);
			if(pipes == 0)
				return ;
		//	printf("number of pipes are >> %d\n", pipes_count);
		}
		i++;
	}
	ft_assign_tpipe(pipes, pipes_count , envp);
	execute_pipe(exec, 0, -1, pipes);
	printf("%d\n", pipes_count);
	printf("%s\n", exec->command[pipes_count]);
	if(ft_strcmp(exec->command[pipes_count], ">") == 0)
		ft_advanced_redirect(exec, envp, pipes_count);
	// command_parser = ft_split(exec->command[0], ' ');
	// printf("%s\n", ft_exec_command(envp, exec->command[0]));
	// pid = fork();
	// if (pid == 0)
	// 	printf("%d\n", execve(ft_exec_command(envp, command_parser[0]), command_parser, envp));
	// wait(NULL);
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
			ft_fill_exec(&exec, lst);
			ft_print_exec(&exec);
			ft_mini(&exec, envp, &pipes);
			wait(NULL);
			// printf("\nTOKEN LIST\n\n");
			// print_lst(lst);
			// printf("\nREDIR LIST\n\n");
			// print_redir(redir);
		}
	}
	return (0);
}
