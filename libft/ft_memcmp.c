/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:54:18 by jissa             #+#    #+#             */
/*   Updated: 2025/05/24 18:02:25 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr_1;
	const unsigned char	*ptr_2;
	size_t				i;

	ptr_1 = (unsigned char *)s1;
	ptr_2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr_1[i] != ptr_2[i])
			return (ptr_1[i] - ptr_2[i]);
		i++;
	}
	return (0);
}
