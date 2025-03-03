/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:43:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:54:22 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// tous les philosophes doivent commencer leur routine en meme temps, il faut donc attendre qu'ils tous prets.
static void	wait_for_all_philos(t_data *data)
{
	while (data->threads_ready == false)
		; // ne fait rien, tourne en boucle
}

void	*philo_routine(void *argt)
{
	t_philo	*philo;
	
	philo = (t_philo *)argt;
	wait_for_all_philos(philo->data);
	philo->last_meal_time = ;//todo
	while (!philo->data->the_end)
	{
		if (philo->finished)
			return (NULL);
		//eat
		//printf
		//usleep
		
		//sleep
		//printf
		//usleep
		
		//think
		//printf
	}
	return (NULL);
}

bool	thread_action(pthread_t thread, t_action action, void *(*routine)(void *),
	void *argt)
{
	if (action == CREATE)
		if (pthread_create(thread, NULL, routine, argt) != 0)
			return (thread_mutex_error(action));
	else if (action == JOIN)
		if (pthread_join(thread, NULL) != 0)
			return (thread_mutex_error(action));
	else if (action == DETACH)
		if (pthread_detach(thread) != 0)
			return (thread_mutex_error(action));
	return (true);
}
