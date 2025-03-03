/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:28:02 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:57:12 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// retourne le temps en millisecondes ou -1 en cas d'erreur
long	timer(void)
{
	struct timeval	time_struct; // contient secondes : tv_sec et microsecondes : tv_usec
	long			time;
	
	if (gettimeofday(&time_struct, NULL) != 0)
	{
		printf("Gettimeofday function error\n");
		return (-1);
	}
	time = time_struct.tv_sec * 1000 + (time_struct.tv_usec / 1000); //conversion des s et des micros en ms
	return (time);
}

void	waiting(long time, t_data *data)
{
	
}
