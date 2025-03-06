/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:35:46 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/06 18:58:55 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	*one_routine(void *argt)
{
	t_philo	*philo;
	t_data	*data;
	bool	end;

	philo = (t_philo *)argt;
	data = philo->data;
	set_long(&philo->lock, &philo[0].last_meal_time,
		(timer() - get_long(&data->sim_lock, data->start_time)));
	if (!print_action(philo, data, FIRST) || !print_action(philo, data, THINK))
		return (NULL);
	while (1)
	{
		mutex_option(&data->sim_lock, LOCK);
		end = data->the_end;
		mutex_option(&data->sim_lock, UNLOCK);
		if (end)
			break ;
		usleep(9);
	}
	return (NULL);
}

static void	only_one_philo(t_philo *philo, t_data *data)
{
	if (set_long(&data->sim_lock, &data->start_time, timer()) == -1)
		return ;
	thread_option(&philo[0].tid, CREATE, one_routine, philo);
	return ;
}

static bool	death(t_data *data, t_philo *philo)
{
	long	time_passed;

	if (!mutex_option(&philo->lock, LOCK)
		|| !mutex_option(&data->sim_lock, LOCK))
		return (false);
	time_passed = timer() - data->start_time - philo->last_meal_time;
	if (!mutex_option(&philo->lock, UNLOCK)
		|| !mutex_option(&data->sim_lock, UNLOCK))
		return (false);
	if (time_passed > get_long(&data->sim_lock, data->time2die))
	{
		set_bool(&data->sim_lock, &data->the_end, true);
		print_action(philo, data, DIED);
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
	while (!get_bool(&data->sim_lock, data->the_end))
	{
		i = 0;
		nb_of_finished_philos = 0;
		while (i < get_long(&data->sim_lock, data->philo_nb))
		{
			if (death(data, &data->philos[i]))
				break ;
			mutex_option(&data->philos[i].lock, LOCK);
			if (data->philos[i].finished == true)
				nb_of_finished_philos++;
			mutex_option(&data->philos[i].lock, UNLOCK);
			i++;
		}
		if (nb_of_finished_philos == get_long(&data->sim_lock, data->philo_nb))
			set_bool(&data->sim_lock, &data->the_end, true);
	}
	return (NULL);
}

void	simulation(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	if (data->min_meals == 0 || data->philo_nb == 0)
		return ;
	if (data->philo_nb == 1)
		only_one_philo(philos, data);
	else
	{
		if (set_long(&data->sim_lock, &data->start_time, timer()) == -1)
			return ;
		while (i < data->philo_nb)
		{
			if (!thread_option(&philos[i].tid, CREATE, ph_routine, philos + i))
				return ;
			i++;
		}
	}
	if (!thread_option(&data->monitor, CREATE, monitoring, data))
		return ;
	i = 0;
	while (i < data->philo_nb)
		thread_option(&data->philos[i++].tid, JOIN, NULL, NULL);
	set_bool(&data->sim_lock, &data->the_end, true);
	thread_option(&data->monitor, JOIN, NULL, NULL);
}
