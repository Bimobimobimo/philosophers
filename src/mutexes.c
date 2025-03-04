/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:52:36 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 10:18:32 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	mutex_option(pthread_mutex_t *mutex, t_option choice)
{
	if (choice == INIT)
	{
		if (pthread_mutex_init(mutex, NULL) != 0)
			return (thread_mutex_error(choice));
	}
	else if (choice == DESTROY)
	{
		if (pthread_mutex_destroy(mutex) != 0)
			return (thread_mutex_error(choice));
	}
	else if (choice == LOCK)
	{
		if (pthread_mutex_lock(mutex) != 0)
			return (thread_mutex_error(choice));
	}
	else if (choice == UNLOCK)
	{
		if (pthread_mutex_unlock(mutex) != 0 )
			return (thread_mutex_error(choice));
	}
	return (true);
}
