/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:43:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 14:26:22 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// tous les philosophes doivent commencer leur routine en meme temps, il faut donc attendre qu'ils tous prets.
static void	wait_for_all_philos(t_data *data)
{
	while (data->threads_ready == false)
		; // ne fait rien, tourne en boucle
}

static bool	taking_forks(t_philo *philo)
{
	if (philo->id % 2 == 0) //pair
	{
		if (!mutex_option(&philo->right_fork->fork, LOCK, "fork"))
			return (false);
		if (!print_action(philo, philo->data, RIGHT))
			return (false);
		if (!mutex_option(&philo->left_fork->fork, LOCK, "fork"))
			return (false);
		if (!print_action(philo, philo->data, LEFT))
			return (false);
	}
	else //impair
	{
		if (!mutex_option(&philo->left_fork->fork, LOCK, "fork"))
			return (false);
		if (!print_action(philo, philo->data, LEFT))
			return (false);
		if (!mutex_option(&philo->right_fork->fork, LOCK, "fork"))
			return (false);
		if (!print_action(philo, philo->data, RIGHT))
			return (false);
	}	
	return (true);
}

static bool	eating(t_philo *philo)
{
	philo->last_meal_time = timer(); //microsecondes pour precision
	if (philo->last_meal_time < 0)
		return (false);
	philo->meals_counter++;
	waiting(philo->data->time2eat, philo->data);
	if (!print_action(philo, philo->data, EAT))
		return (false);
	if (philo->meals_counter >= philo->data->min_meals)
		philo->finished = true;
	if (!mutex_option(&philo->left_fork->fork, UNLOCK, "fork")
		|| !mutex_option(&philo->right_fork->fork, UNLOCK, "fork"))
		return (false);
	return (true);
}

void	*philo_routine(void *argt)
{
	t_philo	*philo;
	
	philo = (t_philo *)argt;
	wait_for_all_philos(philo->data);
	philo->last_meal_time = philo->data->start_time;
	while (!philo->data->the_end)
	{
		if (philo->finished)
			return (NULL);
		if (!taking_forks(philo))
		{
			printf("Taking_forks error in threads.c\n");
			return (NULL);
		}
		if (!eating(philo))
		{
			printf("Eating error in threads.c\n");
			return (NULL);
		}
		if (!print_action(philo, philo->data, SLEEP))
			return (NULL);
		waiting(philo->data->time2sleep, philo->data);
		if (!print_action(philo, philo->data, THINK))
			return (NULL);
	}
	return (NULL);
}

bool	thread_option(pthread_t thread, t_option choice, void *(*routine)(void *),
	void *argt)
{
	if (choice == CREATE)
	{
		if (pthread_create(&thread, NULL, routine, argt) != 0)
			return (thread_mutex_error(choice));
		else
			printf("Thread created\n");
	}
	else if (choice == JOIN)
	{
		if (pthread_join(thread, NULL) != 0)
			return (thread_mutex_error(choice));
		else
			printf("Thread joined\n");
	}
	else if (choice == DETACH)
	{
		if (pthread_detach(thread) != 0)
			return (thread_mutex_error(choice));
		else
			printf("Thread detached\n");
	}
	return (true);
}
