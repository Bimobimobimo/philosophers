/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:29:00 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 10:16:54 by lcollong         ###   ########.fr       */
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
			mutex_option(&data->philos->left_fork->fork, DESTROY);
			free(&data->forks[i]);
			i++;
		}
	}
	i = 0;
	if (data->philos)
	{
		while (&data->philos[i])
		{
			mutex_option(&data->philos->philo_mutex, DESTROY);
			free(data->philos);
			i++;
		}
	}
	if (data)
	{
		mutex_option(&data->sim_mutex, DESTROY);
		mutex_option(&data->print_mutex, DESTROY);
		free(data);
	}
}
