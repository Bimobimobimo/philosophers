/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 11:29:00 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 17:28:00 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	if (data && data->forks)
	{
		while (i++ < data->philo_nb)
			mutex_option(&data->philos->first_fork->lock, DESTROY);
		free(data->forks);
	}
	i = 0;
	if (data && data->philos)
	{
		while (i++ < data->philo_nb)
			mutex_option(&data->philos->lock, DESTROY);
		free(data->philos);
	}
	if (data)
	{
		mutex_option(&data->sim_lock, DESTROY);
		mutex_option(&data->print_lock, DESTROY);
		free(data);
	}
}
