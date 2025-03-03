/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:29:00 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:08:33 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (&data->forks[i])
		{
			free(&data->forks[i]);
			i++;
		}
	}
	i = 0;
	if (data->philos)
	{
		while (&data->philos[i])
		{
			free(data->philos);
			i++;
		}
	}
	if (data)
		free(data);
}
