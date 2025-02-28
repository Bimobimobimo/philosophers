/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:43:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/28 15:57:26 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	routine(t_data *data)
{
	
}

bool	thread_action(pthread_t thread, t_action action, void *(*routine)(void *),
	t_data *data)
{
	if (action == CREATE)
		if (pthread_create(thread, NULL, routine, data) != 0)
			return (thread_error(action));
	else if (action == JOIN)
		if (pthread_join(thread, NULL) != 0)
			return (thread_error(action));
	else if (action == DETACH)
		if (pthread_detach(thread) != 0)
			return (thread_error(action));
	return (true);
}
