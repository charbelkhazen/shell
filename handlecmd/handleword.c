/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleword.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 11:33:50 by jissa             #+#    #+#             */
/*   Updated: 2025/09/04 11:34:17 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_free(char *a, char *b)
{
	char	*r;

	r = ft_strjoin(a, b);
	free(a);
	free(b);
	return (r);
}

char	*handleword(char *buf, int status)
{
	int		tok;
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
