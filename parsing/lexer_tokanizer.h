/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokanizer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:06:09 by rimney            #+#    #+#             */
/*   Updated: 2022/04/15 06:30:03 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_TOKINAZER_H
# define LEXER_TOKINAZER_H
# include "../minishell.h"

typedef enum e_type
{
	TOKEN_TEXT,
	TOKEN_LEFT_ARROW,
	TOKEN_RIGHT_ARROW,
	TOKEN_PIPE,
	TOKEN_DOUBLE_LEFT_ARROW,
	TOKEN_DOUBLE_RIGHT_ARROW,
	TOKEN_EOF,
} t_types;

typedef	struct	s_token
{
	char	*value;
	t_types type;
}	t_token;

typedef struct s_lexer
{
	char			*src;
	int				src_len;
	char			c;
	char			next_c;
	unsigned int	i;
}	t_lexer;

t_token *token_init(int type, char *value);
t_lexer *lexer_init(char *value);

# endif