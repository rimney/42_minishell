/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:22 by rimney            #+#    #+#             */
/*   Updated: 2022/06/25 01:52:14 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define GREEN_COLOR "\e[0;32m"
# define WHITE_COLOR "\033[0;37m"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include "afaf/parsing.h"
//# include "parsing/lexer_tokanizer.h"

typedef struct s_env
{
    char    **envp;
	char	**export;
    int     exit_value;
} t_env;

typedef struct s_pipe
{
	
	int fd[2];
	int in;
	int max;
	int in_save;
	t_env *env;
} t_pipe;

typedef struct s_exec
{
	char **command;
	int input_count;
	int input_flag;
	int redirection_count;
	int redirecion_flag;
	int append_count;
	int append_flag;
	int heredoc_count;
	int heredoc_flag;
	int pipe_count;
	int pipe_flag;
	int args;
	int initial_flag;
	int sev_flag;
    char    **envp;
	char	**export;
	t_env env;
} t_exec;

int ft_strcmp(char *s1, char *s2);
void    ft_pwd(t_env *env);

char *ft_substr(char const *s, unsigned int start, int len);
char    *ft_strjoin(char *s1, char *s2, char *s3);
char	**ft_split(char const *s, char c);
int     ft_strncmp(char *s1, char *s2, int n);
void	ft_single_append(int argc, char **argv);
int	ft_append(int index, t_exec *exec, t_pipe *tpipe, int command_location);;
char	*ft_exec_command(char **envp, char *command);
void	ft_advanced_append(int argc, char **argv, char **envp, int i);
int ft_is_space(char *str);
char	*ft_locate_env(char **env);
char	*ft_filter_command(char *command);
void	ft_free(char **value);
void	ft_single_redirect(char *argv);
char	*ft_is_a_command(char **env, char *command);
int	ft_redirect(int index, t_exec *exec, int command_location);
void    ft_print_history(char *history);
int	ft_count_elements(char **str);
char	*ft_check_command(char **env, char *command);
int ft_exec_heredoc(t_exec *exec, int index, int fd[2], int command_location);
int ft_basic_heredoc(t_exec *exec, int index);
int ft_get_last_delimiter(t_exec *exec,  int index);
int ft_execute_heredoc(t_exec *exec, t_pipe *pipes, int index);
int ft_execute_heredoc(t_exec *exec, t_pipe *pipes, int index);
int    ft_env(t_env *env);
char    *ft_strdup(char *s1, int flag);
void    ft_get_env(t_exec *exec, char **env);
int ft_find_variable_index(char *str, char c);
int ft_count_elements(char **str);
int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe);
void	ft_assign_tpipe(t_pipe *pipe, int argc);
void    ft_get_env(t_exec *exec, char **env);
void	ft_advanced_redirect(t_exec *exec, char **envp, int i, t_pipe *tpipe);
void    ft_execute_command(t_exec *exec, int index);
int only_pipe_flag(t_exec *exec);
int    ft_redirect_input(t_exec *exec, t_pipe *tpipe, int index, int command_location);
 void   ft_apply_input_redirection_after_pipe(int in, int out, t_pipe *tpipe, t_exec *exec, int index);
int	ft_count_till_other_token(t_exec *exec, int index, char *token);
int ft_apply_pipe_middle(t_exec *exec, t_pipe *tpipe, int i, int fd);
int	ft_dup_and_redirect(int fd_in, t_exec *exec, int index);
int	ft_mini_pipe(t_exec *exec, t_pipe *pipes, int in, int count, int index);
int ft_is_another_flag(t_exec *exec, int index);
int ft_apply_redin_middle(t_exec *exec, t_pipe *tpipe,  int i);
int	ft_middle_rediout(t_exec *exec, t_pipe *tpipe, int i);
# endif