/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 12:20:10 by atarchou          #+#    #+#             */
/*   Updated: 2022/05/31 14:15:16 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_token_list_end(t_token **lst_token, int nbwords)
{
	t_token	*lst;

	lst = *lst_token;
	if (nbwords - 1 != 0)
		lst->next = (t_token *)malloc(sizeof(t_token));
	else
		lst->next = NULL;
}

t_token	*token_split(char const *s, char c)
{
	int		nbwords;
	int		i;
	t_token	*lst;
	t_token	*head;

	nbwords = ft_words((char *)s, c);
	lst = (t_token *)malloc(sizeof(t_token));
	head = lst;
	i = 0;
	while (nbwords)
	{
		while (*s == c && *s != '\0')
			s++;
		lst->value = ft_strsub((char *)s, 0, ft_letters((char *)s, c));
		lst->type = types(lst);
		if (!lst->value)
			return (NULL);
		s = s + ft_letters((char *)s, c);
		check_token_list_end(&lst, nbwords);
		lst = lst->next;
		nbwords--;
	}
	return (head);
}

void	error_exit(char *str)
{
	printf ("%s\n", str);
	exit(0);
}

t_redir	*parser(t_token *lst, char *line)
{
	t_redir	*redir;
	t_token	*head;

	head = lst;
	redir = NULL;
	if (check_command(lst))
	{
		if (contain(line, '\''))
		{
			if (!check_quotes(line, '\''))
				error_exit("SINGLE QUOTE WRONG\n");
		}
		else if (contain(line, '\"'))
		{
			if (!check_quotes(line, '\"'))
				error_exit("DOUBLE QUOTE WRONG\n");
		}
		parse_env(&lst);
		lst = head;
		redir = fill_redir_lst(redir, lst);
	}
	return (redir);
}
