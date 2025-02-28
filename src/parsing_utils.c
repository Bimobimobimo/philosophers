/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:27:46 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/28 14:03:56 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	atol_philo(const char *nptr)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
		nb = nb * 10 + (nptr[i++] - '0');
	if (nb > INT_MAX)
		return (-1);
	return (nb);
}

bool	too_many_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;	
	if (i > 10)// 2 147 483 647 = 10 chiffres
		return (true);
	return (false);
}

bool	valid_nb(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		return (false);
	if (str[i] == '+')
		i++;
	if (str[i] < '0' && str[i] > '9')
		return (false);
	if (too_many_digits(str + i)) //todo
		return (false);
	return (true);
}
