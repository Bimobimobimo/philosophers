/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:52:36 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:12:47 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	mutex_action(pthread_mutex_t *mutex, t_action action)
{
	if (action == INIT)
		if (pthread_mutex_init(fork, NULL) != 0)
			return (mutex_error(action));
	else if (action == DESTROY)
		if (pthread_mutex_destroy(fork) != 0)
			return (mutex_error(action));
	else if (action == LOCK)
		if (pthread_mutex_lock(fork) != 0)
			return (mutex_error(action));
	else if (action == UNLOCK)
		if (pthread_mutex_unlock(fork) != 0 )
			return (mutex_error(action));
	return (true);
}
