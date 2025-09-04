/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlecmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 10:24:36 by jissa             #+#    #+#             */
/*   Updated: 2025/09/04 10:24:39 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	utiltravword1(int token, char **cur, char **start, char **end)
{
	token = '"';
	(*cur) ++;
	*start = *cur;
	while ((**cur) != '"' && (**cur))
		(*cur)++;
	*end = *cur;
	(*cur) ++;
	return (token);
}

int	utiltravword2(int token, char **cur, char **start, char **end)
{
	token = '\'';
	(*cur) ++;
	*start = *cur;
	while ((**cur) != '\'' && (**cur))
		(*cur)++;
	*end = *cur;
	(*cur) ++;
	return (token);
}

int	travword(char **cur, char **start, char **end) //start and end can never be null here
{
	int	token;

	if (**cur == 0)
		token = 0;
	else if ((**cur) == '"')
		return (utiltravword1(token, cur, start, end));
	else if ((**cur) == '\'')
		return (utiltravword2(token, cur, start, end));
	else
	{
		*start = *cur;
		token = 'w';
		while (**cur && (!ft_strchr("' \"", **cur)))
			(*cur) ++;
		*end = *cur;
	}
	return (token);
}

char	*expand_slice(char *start, char *end, int tok, int status) {
    char	*tmp;
    char	*res;

    tmp = getstr(start, end); 
    if (!tmp)
    	return (ft_strdup(""));
    res = applyexp(tmp, tok, status);
    return (res);
}

char *join_free(char *a, char *b)
{
    char *r;

    r = ft_strjoin(a, b);
    free(a);
    free(b);
    return r;
}

char *handleword(char *buf, int status)
{
    int	tok;
    char	*start;
    char	*end;
    char	*out;
    char	*exp;

    if (!buf || !*buf)
    	return (0);
    out = ft_strdup("");
    tok = travword(&buf, &start, &end);
    while (tok)
    {
        exp = expand_slice(start, end, tok, status);
        out = join_free(out, exp);
        tok = travword(&buf, &start, &end);
    }
    return (out);
}
/*
int main()
{
	int	tok;
	char *start; 
	char *end;
	char *updated;

	char *word = ft_strdup("$hihihi");
	updated =  handleword(word, 12);
	free(word);
	printf("%s\n", updated);
	if (updated)
		free(updated);
}
*/
