/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rimney <rimney@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 20:41:10 by rimney            #+#    #+#             */
/*   Updated: 2022/04/16 23:22:54 by rimney           ###   ########.fr       */
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
	printf("token : %s\n", token->value);
	return (token);
}

char *ft_substr(char const *s, unsigned int start, int len)
{
	int	i;
	int	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
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
	token = token_init(type, str);
	ft_increment_lexer(lexer);
	printf("%s\n", str);
	return (token);
}

t_token	*ft_handle_quotes(t_lexer *lexer, char quote, int index)
{
	int init_value;
	
	init_value = index;
	printf("%d << init_value  value before\n", init_value);
	printf("%d << lexer->i value before\n", lexer->i);
	while(lexer->src[lexer->i] != quote)
		ft_increment_lexer(lexer);
	printf("%d << init_value  value after\n", init_value);
	printf("%d << lexer->i value before\n", lexer->i);
	return(ft_set_token(lexer, ft_substr(lexer->src, init_value, lexer->i - 1), TOKEN_TEXT));
}

t_token	*ft_get_token(t_lexer *lexer)
{
	t_token *token;

	while(lexer->i < strlen(lexer->src))
	{
		if(lexer->c == ' ' || lexer->c == '\t')
			ft_lexer_skip_whitespace(lexer);
		else if(lexer->c == '>' && lexer->next_c == '>')
		{
			ft_increment_lexer(lexer);
			return(ft_set_andvanced_token(lexer, ">>", TOKEN_DOUBLE_RIGHT_ARROW));
		}
		else if(lexer-> c == '<' && lexer->next_c == '<')
		{
			ft_increment_lexer(lexer);
			return (ft_set_andvanced_token(lexer, "<<", TOKEN_DOUBLE_LEFT_ARROW));
		}
		else if(lexer->c == '>' && lexer->next_c != '>')
			return(ft_set_token(lexer, ">", TOKEN_RIGHT_ARROW));
		else if(lexer->c == '<')
			return (ft_set_token(lexer, "<", TOKEN_LEFT_ARROW));
		else if(lexer->c == '|')
			return(ft_set_token(lexer, "|", TOKEN_PIPE));
		else if(lexer->c == '"')
		{
			token = ft_handle_quotes(lexer, lexer->c, lexer->i);
			return (token);
		}
		else
			ft_increment_lexer(lexer);
	}
	return (token);
}


void    ft_parse_line(char *line)
{
    t_lexer *lexer;
	t_token *token;

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
		if(ft_strcmp(line, "pwd") == 0)
		{
			ft_cd(argv[2]);
			printf("%s\n", argv[3]);
		}
		ft_parse_line(line);
    }
    return (0);
}