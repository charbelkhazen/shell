/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:14:03 by jissa             #+#    #+#             */
/*   Updated: 2025/05/27 16:31:13 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	digits_counter(int num)
{
	int	count_of_div;

	count_of_div = !num;
	while (num)
	{
		num = num / 10;
		count_of_div++;
	}
	return (count_of_div);
}

char	*ft_itoa(int n)
{
	long	nb;
	int		len;
	char	*res;

	nb = n;
	len = digits_counter(nb) + (nb < 0);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb >= 10)
	{
		res[len--] = nb % 10 + '0';
		nb /= 10;
	}
	res[len] = nb + '0';
	return (res);
}

/*int    main(void)
{
    int num = -78464;
    printf("%s\n", ft_itoa(num));
    return (0);
}*/