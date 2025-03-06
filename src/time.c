/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 16:47:33 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// retourne le temps en microsecondes ou -1 en cas d'erreur
long	timer(void)
{
	struct timeval	time_struct; // contient secondes : tv_sec et microsecondes : tv_usec
	long			time;
	
	if (gettimeofday(&time_struct, NULL) != 0)
	{
		printf("Gettimeofday function error\n");
		return (-1);
	}
	time = time_struct.tv_sec * 1000 + time_struct.tv_usec / 1000;
	return (time); //ms
}

/* void	waiting(long time, t_data *data)
{
	long	start;
	long	passed;
	long	remains;
	
	start = timer();
	while (timer() - start < time)
	{
		if (data->the_end)	
			break;
		passed = timer() - start;
		remains = time - passed;
		usleep(remains); //! pas sur
	}
} */

// eviter les injustices en cas de nombre impair de philosophes
bool	desynchronize_philos(t_philo *philo, t_data *data)
{
	long	time2sleep;
	
	time2sleep = 0;
	if (data->philo_nb % 2 == 0) //nb pair de philosophes
	{
		if (philo->id % 2 == 0)
			usleep(10);
	}
	else //nb impair de philosophes
	{
		if (philo->id % 2 != 0) //id impair
			usleep(10);
		// if (philo->id % 2 == 0)
		// {
		// 	if (!print_action(philo, data, SLEEP))
		// 		return (false);
		// 	time2sleep = (data->time2eat * 2 - data->time2sleep);
		// 	if (time2sleep < 0)
		// 		time2sleep = 0;
		// 	if (!usleep(0.1 * time2sleep * 1000)) //desynchro de 10% du time2sleep en microsecondes
		// 		return (false);
		// }
	}
	return (true);
}
