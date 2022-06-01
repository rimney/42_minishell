/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 01:16:28 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 13:41:29 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_tokanizer.h"

t_token *token_init(int type, char *value)
{
    t_token *token;

    token = malloc(sizeof(t_token));
    token->value = value;
    token->type = type;

    return (token);
}

t_lexer *lexer_init(char *value)
{
    t_lexer *lexer;

    lexer = malloc(sizeof(t_lexer));
    lexer->src = value;
    lexer->i = 0;
    lexer->c = lexer->src[lexer->i];
    lexer->next_c = lexer->src[lexer-> i + 1];
    lexer->src_len = strlen(value);
    return lexer;
}

t_lexer l_advance(t_lexer *lexer)
{
    
}