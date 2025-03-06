/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:52:36 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 17:25:22 by lcollong         ###   ########.fr       */
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
		if (pthread_mutex_unlock(mutex) != 0)
			return (thread_mutex_error(choice));
	}
	return (true);
}

bool	get_bool(pthread_mutex_t *mutex, bool value)
{
	bool	result;

	if (!mutex_option(mutex, LOCK))
		return (false);
	result = value;
	if (!mutex_option(mutex, UNLOCK))
		return (false);
	return (result);
}

bool	set_bool(pthread_mutex_t *mutex, bool *value, bool result)
{
	if (!mutex_option(mutex, LOCK))
		return (false);
	*value = result;
	if (!mutex_option(mutex, UNLOCK))
		return (false);
	return (result);
}

long	get_long(pthread_mutex_t *mutex, long value)
{
	long	result;

	if (!mutex_option(mutex, LOCK))
		return (-1);
	result = value;
	if (!mutex_option(mutex, UNLOCK))
		return (-1);
	return (result);
}

long	set_long(pthread_mutex_t *mutex, long *value, long result)
{
	if (!mutex_option(mutex, LOCK))
		return (-1);
	*value = result;
	if (!mutex_option(mutex, UNLOCK))
		return (-1);
	return (result);
}
