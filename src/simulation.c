/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:46 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 13:46:05 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	only_one_philo(t_philo *philo, t_data *data)
{
	// data->threads_ready = true;
	philo[0].last_meal_time = timer();
	if (!print_action(philo, data, FIRST) || !print_action(philo, data, SLEEP)) //ne peut pas manger car une seule fourchette !
		return ;
	while (!data->the_end)
		usleep(100);
	return ;
}

static bool	death(t_data *data, t_philo *philo)
{
	long	time_passed;

	if (!mutex_option(&philo->lock, LOCK) || !mutex_option(&data->sim_lock, LOCK))
		return (false);
	time_passed = timer() - data->start_time - philo->last_meal_time;
	if (!mutex_option(&philo->lock, UNLOCK) || !mutex_option(&data->sim_lock, UNLOCK))
		return (false);
	if (time_passed >= get_long(&data->sim_lock, data->time2die))
	{
		// //debug
		// printf("Time to die = %ld, or time passed = %ld\n", data->time2die, time_passed);
		// //
		print_action(philo, data, DIED); //pas de check d'erreur car on retournera DEATH dans les 2 cas
		return (true);
	}	
	return (false);
}

void	*monitoring(void *argt)
{
	int		i;
	int		nb_of_finished_philos;
	t_data	*data;

	data = (t_data *)argt;
	//debug
	printf(YELLOW "Entered monitoring...\n" RESET);
	//
	while (!get_bool(&data->sim_lock, data->the_end))
	{
		i = 0;
		nb_of_finished_philos = 0;
		while (i < get_long(&data->sim_lock, data->philo_nb))
		{
			if (death(data, &data->philos[i]))
			{
				set_bool(&data->sim_lock, &data->the_end, true);
				break ;
			}
			if (!mutex_option(&data->philos[i].lock, LOCK))
				return (NULL);
			if (data->philos[i].finished == true)
				nb_of_finished_philos++;
			if (!mutex_option(&data->philos[i].lock, UNLOCK))
				return (NULL);
			i++;
		}
		if (nb_of_finished_philos == get_long(&data->sim_lock, data->philo_nb))
			set_bool(&data->sim_lock, &data->the_end, true);
	}	
	return (NULL);
}

void	simulation(t_data *data)
{
	int	i;

	i = 0;
	if (data->min_meals == 0 || data->philo_nb == 0)
		return ;
	if (data->philo_nb == 1)
		only_one_philo(data->philos, data);
	else
	{
		if (set_long(&data->sim_lock, &data->start_time, timer()) == -1)
			return ;
		// //debug
		// printf(YELLOW "Start time = %ld\n" RESET, get_long(&data->sim_lock, data->start_time));
		// //
		while (i < data->philo_nb) // creation de tous les threads de philos
		{
			if (!thread_option(&data->philos[i].tid, CREATE, philo_routine,
				&data->philos[i]))
				return ;
			// //debug
			// printf(GREEN "Philo numero %d : thread cree\n" RESET, data->philos[i].id);
			// //
			i++;
		}
	}
	
	if (!thread_option(&data->monitor, CREATE, monitoring, data)) // Creation du thread monitoring
		return ;
	// if (!set_bool(&data->sim_lock, data->threads_ready, true))
	// 	return ;

	i = 0;
	while (i < data->philo_nb) 
	{
		if (!thread_option(&data->philos[i].tid, JOIN, NULL, NULL))
			return ;
		i++;
	}

	set_bool(&data->sim_lock, &data->the_end, true);
	if (!thread_option(&data->monitor, JOIN, NULL, NULL))
		return ;
}
