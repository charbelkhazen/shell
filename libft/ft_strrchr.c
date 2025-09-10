/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:26:32 by jissa             #+#    #+#             */
/*   Updated: 2025/05/28 11:27:39 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*last_occurence = NULL;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
		{
			last_occurence = &s[i];
		}
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return ((char *)last_occurence);
}
