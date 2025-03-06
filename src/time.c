/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 17:37:16 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	timer(void)
{
	struct timeval	time_struct;
	long			time;

	if (gettimeofday(&time_struct, NULL) != 0)
	{
		printf("Gettimeofday function error\n");
		return (-1);
	}
	time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (time);
}

// eviter les injustices en cas de nombre impair de philosophes
bool	desynchronize_philos(t_philo *philo, t_data *data)
{
	long	time2sleep;

	time2sleep = 0;
	if (data->philo_nb % 2 == 0)
	{
		if (philo->id % 2 == 0)
			usleep(10);
	}
	else
	{
		if (philo->id % 2 != 0)
			usleep(10);
	}
	return (true);
}
