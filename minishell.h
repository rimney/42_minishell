/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:22 by rimney            #+#    #+#             */
/*   Updated: 2022/04/17 00:40:49 by rimney           ###   ########.fr       */
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
# include "parsing/lexer_tokanizer.h"

int ft_cd(char *path);
char    ft_strcmp(char *s1, char *s2);
void    ft_pwd(void);
void    ft_echo(char *str, int flag);
char *ft_substr(char const *s, unsigned int start, int len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int     ft_strncmp(char *s1, char *s2, int n);
# endif