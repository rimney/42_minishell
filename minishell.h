/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:22 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 16:54:36 by rimney           ###   ########.fr       */
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
    int     exit_value;
    char    *pwd;
    char    **history; // not sure about this ??
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
	char **redirections;
	char **files;
} t_exec;

int ft_strcmp(char *s1, char *s2);
void    ft_pwd(t_env *env);

char *ft_substr(char const *s, unsigned int start, int len);
char    *ft_strjoin(char *s1, char *s2, char *s3);
char	**ft_split(char const *s, char c);
int     ft_strncmp(char *s1, char *s2, int n);
void	ft_single_append(int argc, char **argv);
int	ft_append(int argc, char **argv, char **envp);
char	*ft_exec_command(char **envp, char *command);
void	ft_advanced_append(int argc, char **argv, char **envp, int i);
int ft_is_space(char *str);
char	*ft_locate_env(char **env);
char	*ft_filter_command(char *command);
void	ft_free(char **value);
void	ft_single_redirect(int argc, char **argv);
void    ft_advanced_redirect(t_exec *exec, char **envp, int i);
char	*ft_is_a_command(char **env, char *command);
int	ft_redirect(int argc, char **argv, char **envp);
void    ft_print_history(char *history);
int	ft_count_elements(char **str);
char	*ft_check_command(char **env, char *command);
int ft_get_last_delimiter(int argc, char **argv, int index);
int ft_exec_heredoc(char **argv, char **envp, int index, int fd[2]);
void ft_heredoc(int argc, char **argv, char **envp, int index);
int    ft_env(t_env *env);
char    *ft_strdup(char *s1, int flag);
void    ft_get_env(t_env *env, char **envp);
int ft_find_variable_index(char *str, char c);
int ft_count_elements(char **str);
int	ft_append(int argc, char **argv, char **envp);
int    ft_redirect_input(int argc, char **argv, char **envp);
int ft_execute_heredoc(int argc, char **argv, char **envp);
int ft_count_elements(char **str);
int execute_pipe(t_exec *exec, int index, int in,  t_pipe *tpipe);
void	ft_assign_tpipe(t_pipe *pipe, int argc, char **envp);
void    ft_get_env(t_env *env, char **envp);
# endif