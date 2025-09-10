/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:22:48 by jissa             #+#    #+#             */
/*   Updated: 2025/05/27 15:28:56 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}

/*
{
	char buffer[10] = "abcdefghi";
	printf("before the ft_bzero invocation: %s\n", buffer);
	ft_bzero(buffer + 3, 0);
	printf("after the bzero invocation: %s\n", buffer);
	return 0;
}*/