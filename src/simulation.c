/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:46 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:59:03 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	only_one_philo(void)
{
	return ;
}

void	*monitoring(t_data *data)
{
	
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->min_meals == 0 || data->philo_nb == 0)
		return ;
	if (data->philo_nb == 1)
		return (only_one_philo()); //todo
	else
	{
		while (i < data->philo_nb)
		{
			if (!thread_action(&data->philos[i].tid, CREATE, philo_routine,
				&data->philos[i]))
				return ;
			i++;
		}
	}
	data->start_time = timer(); // start time !
	data->threads_ready = true;

	//? comment determiner qu'on ne veut joindre que qd tt le monde a fini ?
	i = 0;
	while (i < data->philo_nb)
	{
		if (!thread_action(&data->philos[i], JOIN, NULL, NULL))
			return ;
		i++;
	}

	
	
	// if (!thread_action(&data->monitor, CREATE, monitoring, data))
	// 	return ;
	
}
