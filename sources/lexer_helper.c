/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvoloshy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:07:26 by mvoloshy          #+#    #+#             */
/*   Updated: 2024/10/10 22:23:00 by mvoloshy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*process_str(char *str)
{
	char	*new_str;
	char	opening_quote_type;
	int		i;
	int		count;

	opening_quote_type = '\0';
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			if (opening_quote_type == '\0')
				opening_quote_type = str[i];
			count++;
		}
		i++;
	}
	if (ft_strchr(str, '$'))
		process_env_arg(&str);
	if (opening_quote_type == '\0')
		return (str);
	new_str = remove_quotes(str, opening_quote_type, -1);
	free(str);
	return (new_str);
}

char	*tokenize_input(char **input)
{
	char	*str;
	char	*start;
	int		length;

	start = *input;
	length = ft_strlen(start);
	*input = ft_strpbrk(*input, " >|<&\'\"");
	if (*input)
		if (**input == '\'' || **input == '\"')
			length = handle_quotes(*input);
	str = malloc(sizeof(char) * length + 1);
	if (str == NULL)
	{
		p_error(ALLOC_FAILURE, NULL);
		return (NULL);
	}
	ft_strlcpy(str, start, length + 1);
	return (process_str(str));
}

int	add_to_token_list(t_lexer **lexer, char *str)
{
	t_lexer	*new_token;
	t_lexer	*temp;

	if (!*str)
		return (OK);
	new_token = malloc(sizeof(t_lexer));
	if (new_token == NULL)
		return (p_error(ALLOC_FAILURE, NULL));
	new_token->str = str;
	new_token->token = token_type(str);
	new_token->next = NULL;
	new_token->prev = NULL;
	if (*lexer == NULL)
		*lexer = new_token;
	else
	{
		temp = get_last_token(*lexer);
		temp->next = new_token;
		new_token->prev = temp;
	}
	return (OK);
}
