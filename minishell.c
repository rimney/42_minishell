/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:10 by rimney            #+#    #+#             */
/*   Updated: 2022/04/16 01:00:25 by rimney           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	ft_increment_lexer(t_lexer *lexer)
{
	if (lexer->i < lexer->src_len && lexer->c != 0)
	{
		lexer->i += 1;
		lexer->c = lexer->src[lexer->i];
		lexer->next_c = lexer->src[lexer->i + 1];
	}
	else
		printf("cant do it more");
}

void	ft_lexer_skip_whitespace(t_lexer *lexer)
{
	if (lexer->c == ' ' || lexer->c == '\t')
		ft_increment_lexer(lexer);
}

t_token *ft_set_token(t_lexer *lexer, char *value, t_types type) // we must add a linked list in here !!
{
	char *str;
	t_token *token;

	str = strdup(value);
	token = token_init(type, str);
	ft_increment_lexer(lexer);
	printf("%s\n", token->value);
	return (token);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len1;
	int		len2;
	char	*str;

	if (s1 && s2)
	{
		len1 = strlen(s1);
		len2 = strlen(s2);
		str = (char*)malloc(sizeof(char) * (len1 + len2 + 1));
		if (str == NULL)
			return (NULL);
		i = -1;
		while (s1[++i])
			str[i] = s1[i];
		i = -1;
		while (s2[++i])
		{
			str[len1] = s2[i];
			len1++;
		}
		str[len1] = '\0';
		return (str);
	}
	return (NULL);
}

t_token *ft_set_andvanced_token(t_lexer *lexer, char *value, t_types type)
{
	char *str;
	t_token *token;

	str = strdup(value);
	str = ft_strjoin(str, str);
	token = token_init(type, str);
	ft_increment_lexer(lexer);
	printf("%d\n", lexer->i);
	printf("%s\n", token->value);
	return (token);
}

t_token	*ft_get_token(t_lexer *lexer)
{
	t_token *token;

	while(lexer->c != 0 && lexer->i < strlen(lexer->src))
	{
		if(lexer->c == ' ' || lexer->c == '\t')
			ft_lexer_skip_whitespace(lexer);
		if(lexer->c == '>' && lexer->next_c == '>')
		{
			ft_increment_lexer(lexer);
			return(ft_set_andvanced_token(lexer, &lexer->c, TOKEN_DOUBLE_RIGHT_ARROW));
		}
		else if(lexer->c == '>' && lexer->next_c != '>') // we must ust use substr to join the two "<<";
			return(ft_set_token(lexer, &lexer->c, TOKEN_LEFT_ARROW));
		else if(lexer->c == '|')
			return(ft_set_token(lexer, &lexer->c, TOKEN_PIPE));	
		else if(lexer->c == '<')
			return (ft_set_token(lexer, &lexer->c, TOKEN_RIGHT_ARROW));
		else
			ft_increment_lexer(lexer);
	}
	return (token);
}



void    ft_parse_line(char *line)
{
    t_lexer *lexer;
	t_token *token;

    int i = 0;

    lexer = lexer_init(line);
    while(lexer->i < lexer->src_len)
		token = ft_get_token(lexer);
}

int main(int argc, char **argv, char **envp)
{
    int i = 0;
    char *line;
    char cwd[256];
    while(1)
    {
        printf(GREEN_COLOR);
        line = readline("BomusShell$> \033[0;37m");
        ft_parse_line(line);
    }
    return (0);
}