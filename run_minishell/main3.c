/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jissa <jissa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:36:14 by jissa             #+#    #+#             */
/*   Updated: 2025/09/21 18:36:55 by jissa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input(char *input, char ***env, int *status)
{
	if (unclosedquotes(input))
	{
		free(input);
		return (1);
	}
	if (startbuiltin(input))
	{
		handlestartbuiltin(input, env, status);
		free(input);
		return (1);
	}
	return (0);
}
