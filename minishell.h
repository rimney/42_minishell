/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:22 by rimney            #+#    #+#             */
/*   Updated: 2022/05/22 22:16:40 by rimney           ###   ########.fr       */
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
# include "parsing/lexer_tokanizer.h"

typedef struct s_env
{
    char    **envp;
    int     exit_value;
    char    **set
}


int ft_cd(char *path);
int ft_strcmp(char *s1, char *s2);
void    ft_pwd(void);
void    ft_echo(char *str, int flag);char *ft_substr(char const *s, unsigned int start, int len);
char    *ft_strjoin(char *s1, char *s2, char *s3);
char	**ft_split(char const *s, char c);
int     ft_strncmp(char *s1, char *s2, int n);
void	ft_single_append(int argc, char **argv);
int	ft_append(int argc, char **argv, char **envp);
char	*ft_exec_command(char **envp, char *command);
void	ft_advanced_append(int argc, char **argv, char **envp, int i);
int	ft_is_space(char *str);
char	*ft_locate_env(char **env);
char	*ft_filter_command(char *command);
void	ft_free(char **value);
void	ft_single_redirect(int argc, char **argv);
void	ft_advanced_redirect(int argc, char **argv, char **envp, int i);
char	*ft_is_a_command(char **env, char *command);
int	ft_redirect(int argc, char **argv, char **envp);
void    ft_print_history(char *history);
int	ft_count_elements(char **str);
char	*ft_check_command(char **env, char *command);
int ft_get_last_delimiter(int argc, char **argv, int index);
int ft_exec_heredoc(char **argv, char **envp, int index, int fd[2]);
void ft_heredoc(int argc, char **argv, char **envp, int index);
# endif