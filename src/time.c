/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 14:47:09 by lcollong         ###   ########.fr       */
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
	time = time_struct.tv_sec * 1000 * 1000 + time_struct.tv_usec; //tout en microsec
	return (time);
}

void	waiting(long time, t_data *data)
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
}
