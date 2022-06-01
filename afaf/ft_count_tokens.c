/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney < rimney@student.1337.ma>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 03:42:48 by rimney            #+#    #+#             */
/*   Updated: 2022/06/01 03:49:57 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_pipes(t_token *token)
{
    int i;

    i = 0;
    while(token)
    {
        if(token->type == PIPE)
            i++;
        token = token->next;
    }
    return (i);
}