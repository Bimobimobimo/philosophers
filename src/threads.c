/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:43:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/05 19:38:29 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// // tous les philosophes doivent commencer leur routine en meme temps, il faut donc attendre qu'ils tous prets.
// static bool	wait_for_all_philos(t_data *data)
// {
// 	while (1)
// 	{
// 		if (!mutex_option(&data->sim_lock, LOCK))
// 			return (false);
// 		if (data->threads_ready)
// 		{
// 			if (!mutex_option(&data->sim_lock, UNLOCK))
// 				return (false);
// 			break ;
// 		}
// 		if (!mutex_option(&data->sim_lock, UNLOCK))
// 			return (false);
// 	}
// 	return (true);
// }

static bool	taking_forks(t_philo *philo)
{
	if (!mutex_option(&philo->first_fork->lock, LOCK))
		return (false);
	if (!print_action(philo, philo->data, FIRST))
		return (false);
	if (!mutex_option(&philo->second_fork->lock, LOCK))
		return (false);
	if (!print_action(philo, philo->data, SECOND))
		return (false);	
	return (true);
}

static bool	eating(t_philo *philo)
{
	if (set_long(&philo->lock, philo->last_meal_time, timer()) == -1)
		return (false);
	philo->meals_counter++;
	if (!print_action(philo, philo->data, EAT))
		return (false);
	usleep(philo->data->time2eat * 1000);	
	if (philo->data->min_meals > 0 && philo->meals_counter >= philo->data->min_meals)
		philo->finished = true;
	if (!mutex_option(&philo->first_fork->lock, UNLOCK)
		|| !mutex_option(&philo->second_fork->lock, UNLOCK))
		return (false);
	return (true);
}

static bool	thinking(t_philo *philo)
{
	if (!print_action(philo, philo->data, THINK))
		return (false);
	return (true);
}

void	*philo_routine(void *argt)  
{
	t_philo	*philo;
	
	philo = (t_philo *)argt;
	// wait_for_all_philos(philo->data);
	
	
	if (!desynchronize_philos(philo, philo->data))
		return (NULL);
	
	philo->last_meal_time = get_long(&philo->data->sim_lock, philo->data->start_time);

	while (!get_bool(&philo->data->sim_lock, philo->data->the_end))
	{
		if (philo->finished)
			return (NULL);
		//eat
		if (!taking_forks(philo))
		{
			printf(BOLDRED "Taking_forks error in threads.c\n" RESET);
			return (NULL);
		}
		if (!eating(philo))
		{
			printf(BOLDRED "Eating error in threads.c\n" RESET);
			return (NULL);
		}
		//sleep
		if (!print_action(philo, philo->data, SLEEP))
			return (NULL);
		usleep(philo->data->time2sleep * 1000);
		//think
		if (!thinking(philo))
			return (NULL);
		// usleep(1000);
	}
	return (NULL);
}

bool	thread_option(pthread_t *thread, t_option choice, void *(*philo_routine)(void *),
	void *argt)
{
	if (choice == CREATE)
	{
		if (pthread_create(thread, NULL, philo_routine, argt) != 0)
			return (thread_mutex_error(choice));
		// else
		// 	printf(GREY "Thread created\n" RESET);
	}
	else if (choice == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (thread_mutex_error(choice));
		else
			printf(GREY "Thread joined\n" RESET);
	}
	else if (choice == DETACH)
	{
		if (pthread_detach(*thread) != 0)
			return (thread_mutex_error(choice));
		else
			printf(GREY "Thread detached\n" RESET);
	}
	return (true);
}
