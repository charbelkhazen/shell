/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 15:47:56 by jissa             #+#    #+#             */
/*   Updated: 2025/05/27 16:10:24 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;

	if (size != 0 && nmemb > 4294967295 / size)
		return (NULL);
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	s = (void *)malloc(nmemb * size);
	if (!s)
		return (NULL);
	ft_memset(s, 0, nmemb * size);
	return (s);
}

/*int	main()
{
	int *arr = ft_calloc(5, sizeof(int));
	if (!arr)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
	for (int i = 0; i < 5; i++)
		printf("%d ", arr[i]);
	free(arr);
	return (0);
}*/
