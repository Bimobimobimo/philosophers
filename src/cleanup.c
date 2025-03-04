/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:29:00 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 17:38:30 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data && data->forks)
	{
		while (&data->forks[i])
		{
			mutex_option(&data->philos->left_fork->fork, DESTROY, "fork");
			i++;
		}
		free(data->forks);
	}
	i = 0;
	if (data && data->philos)
	{
		while (&data->philos[i])
		{
			mutex_option(&data->philos->philo_mutex, DESTROY, "philo_mutex");
			i++;
		}
		free(data->philos);
	}
	if (data)
	{
		mutex_option(&data->sim_mutex, DESTROY, "sim_mutex");
		mutex_option(&data->print_mutex, DESTROY, "print_mutex");
		free(data);
	}
}

