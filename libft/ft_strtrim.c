/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 07:58:25 by jissa             #+#    #+#             */
/*   Updated: 2025/05/28 12:19:02 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_equal_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	begin;
	size_t	end;
	char	*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	s1_len = ft_strlen(s1);
	begin = 0;
	end = s1_len;
	while (s1[begin] && is_equal_set(s1[begin], set))
	{
		begin++;
	}
	while (end > begin && is_equal_set(s1[end - 1], set))
	{
		end--;
	}
	trimmed_str = (char *)malloc((end - begin + 1) * sizeof(char));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + begin, end - begin + 1);
	return (trimmed_str);
}

/*int main()
{
	char *str = "   Jihad issa   ";
	char *set = " ";
	printf("%s\n", ft_strtrim(str, set));
	return (0);
}*/