/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: weambros <weambros@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 18:18:46 by weambros          #+#    #+#             */
/*   Updated: 2021/04/16 06:56:46 by weambros         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_token_data(int token, int start, char *line, int *i)
{
	int		end;
	char	*res;

	end = ft_get_token_end(token, i, line, start);
	res = ft_strdup_to_index(line, start, end);
	return (res);
}

int	ft_get_token_end(int token, int *i, char *line, int start)
{
	int	res;

	res = *i + 1;
	if (token >= 5)
		*i += 2;
	else if (line[*i])
		*i += 1;
	while (res > 1 && line[res - 1] != '\\' && (line[res - 1] == ' '
		|| line[res -1] == '>'|| line[res - 1] == '<'
		|| line[res - 1] == '|' || line[res - 1] == '&'
		|| line[res - 1] ==';'))
		res--;
	if (line[res - 1] != '\\' && (line[res - 1] == ' ' || line[res - 1] == '>'
		|| line[res - 1] == '<'|| line[res - 1] == '|' || line[res - 1] == '&'
		|| line[res - 1] ==';'))
		res--;
	if (res < start)
		res = start;
	return (res);
}

void	ft_get_token(char *line, int *i, char **res, int *token)
{
	t_spec_chr	*spec;
	int			start;

	*token = -1;
	if (!line[*i])
		return ;
	spec = ft_init_spec();
	while (line[*i] == ' ')
		(*i)++;
	start = *i;
	while (line[*i])
	{
		ft_switch_quotes(&spec->quote, &spec->quotes, spec->slash, line[*i]);
		*token = ft_istoken(line, i, ft_check_spec(spec));
		if (0 <= *token || !line[*i + 1])
		{
			*res = ft_get_token_data(*token, start, line, i);
			spec = ft_free(spec);
			return ;
		}
		ft_switch_slash(spec, line[*i]);
		(*i)++;
	}
	spec = ft_free(spec);
}

int	ft_istoken_2(char *s, int *i)
{
	int	res;

	res = -1;
	if ((s[*i] == '&' && (s[(*i) + 1]) == '&'))
		res = TOKEN_ANDAND;
	else if (s[*i] == ';')
		res = TOKEN_BIN;
	else if (s[*i] == '|')
		res = TOKEN_PIPE;
	else if (s[*i] == '<')
		res = TOKEN_R_IN;
	else if (s[*i] == '>')
		res = TOKEN_R_OUT;
	else if (!s[*i + 1])
		return (0);
	return (res);
}

int	ft_istoken(char *s, int *i, int spec)
{
	int	res;

	res = -2;
	if (spec)
	{
		if (!s[*i + 1])
			return (0);
		return (res);
	}
	res = ft_istoken_2(s, i);
	if (s[*i] == '\0')
		res = TOKEN_BIN;
	else if (s[*i] == ' ' && s[*i + 1] == '\0')
		res = TOKEN_BIN;
	else if ((s[*i] == '>' && (s[(*i) + 1]) == '>'))
		res = TOKEN_R_D_OUT;
	else if ((s[*i] == '|' && (s[(*i) + 1]) == '|'))
		res = TOKEN_OROR;
	else if (res != -1)
		return (res);
	return (res);
}
