/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:22 by rimney            #+#    #+#             */
/*   Updated: 2022/04/14 02:49:07 by rimney           ###   ########.fr       */
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


char    ft_strcmp(char *s1, char *s2);
void    ft_pwd(void);
void    ft_echo(char *str, int flag);

# endif