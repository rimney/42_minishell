/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:06:02 by atarchou          #+#    #+#             */
/*   Updated: 2022/05/28 16:28:20 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_words(char *s, char c)
{
	int	i;
	int	count;
	int	word;

	i = 0;
	count = 0;
	word = 0;
	while (s[i] != '\0')
	{
		if (word == 0 && s[i] != c)
		{
			word = 1;
			count++;
		}
		else if (word == 1 && s[i] == c)
			word = 0;
		i++;
	}
	return (count);
}

int	ft_letters(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != c && s[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	types(t_token *lst)
{
	if (ft_strcmp(lst->value, "|") == 0)
		lst->type = PIPE;
	else if (ft_strcmp(lst->value, "<") == 0)
		lst->type = REDIROUT;
	else if (ft_strcmp(lst->value, ">") == 0)
		lst->type = REDIRIN;
	else if (ft_strcmp(lst->value, "<<") == 0)
		lst->type = HEREDOC;
	else if (ft_strcmp(lst->value, ">>") == 0)
		lst->type = APPEND;
	else
		lst->type = WORD;
	return (lst->type);
}

int	check_command(t_token *lst)
{
	if (lst->type != 0)
		return (0);
	else
	{
		while (lst)
		{
			if (lst->type != 0 && lst->next == NULL)
				return (0);
			else if (lst->type != 0 && lst->next->type != 0)
				return (0);
			lst = lst->next;
		}
	}
	return (1);
}
