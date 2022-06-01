/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 11:57:55 by atarchou          #+#    #+#             */
/*   Updated: 2022/05/31 16:27:19 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# define GREEN_COLOR "\e[0;32m"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <signal.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>

typedef struct s_token
{
	struct s_token	*next;
	int				type;
	char			*value;
}				t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef enum e_type
{
	WORD,
	REDIRIN,
	REDIROUT,
	APPEND,
	HEREDOC,
	PIPE,
}			t_type;

/******** utils.c functions ********/

int		ft_strcmp(char *s1, char *s2);
char	*ft_strnew(size_t size);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	print_lst(t_token *lst);
void	print_redir(t_redir *lst);

/******* utils_2.c functions ********/

size_t	ft_strlen(const char *str);
int		check_env_var(char *str);
void	parse_env(t_token **lst_token);

/******** parse_token.c functions ********/

int		ft_words(char *s, char c);
int		ft_letters(char *s, char c);
int		types(t_token *lst);
int		check_command(t_token *lst);

/******** parse.c functions ********/

void	check_token_list_end(t_token **lst_token, int nbwords);
void	error_exit(char *str);
t_token	*token_split(char const *s, char c);
t_redir	*parser(t_token *lst, char *line);

/******** redir.c functions ********/

int		count_redir(t_token *lst);
int		check_if_redir(int type);
void	parse_redir(t_redir **lst_redir, t_token *lst_token, int redir_count);
t_redir	*fill_redir_lst(t_redir *lst, t_token *lst_token);

/******** quotes.c functions ********/

int		check_quotes(char *str, char quote);
int		is_operation(char c);
int		check_inside_quotes(char *str);
int		contain(char *str, char c);

/******** signals.c functions ********/

void	handle_sigint(int sig);
#endif