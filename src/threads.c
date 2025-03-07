/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:43:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/07 16:31:51 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
	long	meals_counter;

	if (set_long(&philo->lock, &philo->last_meal_time,
			(timer() - get_long(&philo->data->sim_lock,
					philo->data->start_time))) == -1)
		return (false);
	meals_counter = get_long(&philo->lock, philo->meals_counter);
	set_long(&philo->lock, &philo->meals_counter, meals_counter + 1);
	if (!print_action(philo, philo->data, EAT))
		return (false);
	usleep(philo->data->time2eat * 1000);
	if (!mutex_option(&philo->lock, LOCK))
		return (false);
	if (philo->data->min_meals > 0
		&& philo->meals_counter >= philo->data->min_meals)
		philo->finished = true;
	if (!mutex_option(&philo->lock, UNLOCK))
		return (false);
	if (!mutex_option(&philo->first_fork->lock, UNLOCK)
		|| !mutex_option(&philo->second_fork->lock, UNLOCK))
		return (false);
	return (true);
}

bool	thinking(t_philo *philo)
{
	long	time2eat;
	long	time2sleep;
	long	time2think;

	if (!print_action(philo, philo->data, THINK))
		return (false);
	if (philo->data->philo_nb % 2 == 0)
		return (true);
	time2eat = philo->data->time2eat;
	time2sleep = philo->data->time2sleep;
	time2think = time2eat * 2 - time2sleep;
	if (time2think < 0)
		time2think = 0;
	usleep(time2think * 0.5 * 1000);
	return (true);
}

void	*ph_routine(void *argt)
{
	t_philo	*philo;

	philo = (t_philo *)argt;
	if (!desynchronize_philos(philo, philo->data))
		return (NULL);
	if (!set_long(&philo->lock, &philo->last_meal_time,
			get_long(&philo->data->sim_lock, philo->data->start_time)))
		return (NULL);
	while (!get_bool(&philo->data->sim_lock, &philo->data->the_end))
	{
		if (philo->finished)
			return (NULL);
		if (!taking_forks(philo))
			return (NULL);
		if (!eating(philo))
			return (NULL);
		if (!print_action(philo, philo->data, SLEEP))
			return (NULL);
		usleep(philo->data->time2sleep * 1000);
		if (!thinking(philo))
			return (NULL);
	}
	return (NULL);
}

bool	thread_option(pthread_t *thread, t_option choice,
	void *(*philo_routine)(void *), void *argt)
{
	if (choice == CREATE)
	{
		if (pthread_create(thread, NULL, philo_routine, argt) != 0)
			return (thread_mutex_error(choice));
	}
	else if (choice == JOIN)
	{
		if (pthread_join(*thread, NULL) != 0)
			return (thread_mutex_error(choice));
	}
	return (true);
}
