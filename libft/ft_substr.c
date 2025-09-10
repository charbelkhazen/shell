/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:17:25 by jissa             #+#    #+#             */
/*   Updated: 2025/05/28 11:00:23 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	s_len;
	size_t	i;
	size_t	sub_len;
	char	*sub_str;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	sub_len = s_len - start;
	if (sub_len > len)
		sub_len = len;
	sub_str = (char *)malloc((sub_len + 1) * sizeof(char));
	if (!sub_str)
		return (NULL);
	i = 0;
	while (s[start + i] && i < sub_len)
	{
		sub_str[i] = s[start + i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

/*int main()
{
	const char *str = "Hello World!";
	int start = 6;
	size_t len = 6;
	printf("%s\n", ft_substr(str, start, len));
	return (0);
}*/