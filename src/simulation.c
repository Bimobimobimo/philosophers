/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:46 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 14:23:44 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	only_one_philo(t_philo *philo, t_data *data)
{
	data->threads_ready = true;
	philo[0].last_meal_time = timer();
	if (!print_action(philo, data, LEFT) || !print_action(philo, data, SLEEP)) //ne peut pas manger car une seule fourchette !
		return ;
	while (!data->the_end)
		usleep(100);
	return ;
}

static bool	death(t_philo *philo)
{
	long	time_passed;
	
	if (!mutex_option(&philo->philo_mutex, LOCK, "philo_mutex"))
		return (true);
	time_passed = timer() - philo->last_meal_time;
	if (time_passed >= philo->data->time2die && !philo->finished)
	{
		print_action(philo, philo->data, DIED); //pas de check d'erreur car on retournera DEATH dans les 2 cas
		return (true);
	}
	if (!mutex_option(&philo->philo_mutex, UNLOCK, "philo_mutex"))
		return (true);
	return (false);
}

void	*monitoring(void *argt)
{
	int		i;
	int		nb_of_finished_philos;
	t_data	*data;

	data = (t_data *)argt;
	while (!data->threads_ready) //attend le debut
		;
	while (!data->the_end)
	{
		i = 0;
		nb_of_finished_philos = 0;
		while (&data->philos[i])
		{
			if (death(&data->philos[i]))
				data->the_end = true;
			if (data->philos[i].finished == true)
				nb_of_finished_philos++;
			i++;
		}
		if (nb_of_finished_philos == data->philo_nb)
			data->the_end = true;
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
		return (only_one_philo(data->philos, data)); //todo
	else
	{
		while (i < data->philo_nb)
		{
			if (!thread_option(data->philos[i].tid, CREATE, philo_routine,
				&data->philos[i]))
				return ;
			i++;
		}
	}
	if (!thread_option(data->monitor, CREATE, monitoring, data))
		return ;
	
	printf("\nDEPART !\n\n");
	data->start_time = timer() ; // start time en microsecondes
	i = 0;
	while (&data->philos[i])
	{
		data->philos[i++].last_meal_time = timer();
	}
	// printf("Start time = %ld\n", data->start_time); // en millisecondes
	data->threads_ready = true;
	
	
	//? comment determiner qu'on ne veut joindre que qd tt le monde a fini ?
	i = 0;
	while (i < data->philo_nb)
	{
		if (!thread_option(data->philos[i].tid, JOIN, NULL, NULL))
			return ;
		i++;
	}
	

	
	
	// if (!thread_option(&data->monitor, CREATE, monitoring, data))
	// 	return ;
	
}
