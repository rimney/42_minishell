/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarchou <atarchou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:10:31 by atarchou          #+#    #+#             */
/*   Updated: 2022/05/31 11:49:35 by atarchou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_if_redir(int type)
{
	if (type == 0 || type == 5)
		return (0);
	return (1);
}

int	count_redir(t_token *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		if (check_if_redir(lst->type))
			count++;
		lst = lst->next;
	}
	return (count);
}

void	parse_redir(t_redir **lst_redir, t_token *lst_token, int redir_count)
{
	t_redir	*lst;

	lst = *lst_redir;
	lst->type = lst_token->type;
	lst->file = lst_token->next->value;
	if (redir_count - 1 != 0)
		lst->next = (t_redir *)malloc(sizeof(t_redir));
	else
		lst->next = NULL;
}

t_redir	*fill_redir_lst(t_redir *lst, t_token *lst_token)
{
	t_redir	*head;
	int		counts[2];

	head = NULL;
	counts[0] = 0;
	counts[1] = count_redir(lst_token);
	if (counts[1] == 0)
		return (NULL);
	while (lst_token)
	{
		if (check_if_redir(lst_token->type))
		{
			if (!lst)
				lst = (t_redir *)malloc(sizeof(t_redir));
			parse_redir(&lst, lst_token, counts[1]);
			if (counts[0]++ == 0)
				head = lst;
			counts[1]--;
			lst = lst->next;
		}
		lst_token = lst_token->next;
	}
	return (head);
}
