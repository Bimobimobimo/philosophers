/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/07 15:17:23 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Dire aux philos quelles fourchettes prendre et dans quel ordre.
// philo_index = part de 0, correspond a la position du philosophe,
// alors que philo->id part de 1, c'est son numero.
// Index impair et pair prennent droite et gauche dans ordres differents pour
// eviter deadlock (tout le monde aurait une seule fouchette).
static void	forks_to_philos(t_philo *philo, t_fork *forks, int philo_index)
{
	if (philo->id == philo->data->philo_nb)
	{
		philo->first_fork = &forks[philo_index];
		philo->second_fork = &forks[0];
	}
	else if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[philo_index];
		philo->second_fork = &forks[philo_index + 1];
	}
	else
	{
		philo->first_fork = &forks[philo_index + 1];
		philo->second_fork = &forks[philo_index];
	}
}

bool	init_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->philo_nb)
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].finished = false;
		philos[i].died = false;
		philos[i].data = data;
		philos[i].tid = -1;
		forks_to_philos(&philos[i], data->forks, i);
		if (!mutex_option(&data->philos[i].lock, INIT))
			return (false);
		i++;
	}
	return (true);
}

void	philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb);
	if (!data->philos)
	{
		printf("Malloc error\n");
		return ;
	}
	data->forks = malloc(sizeof(t_fork) * data->philo_nb);
	if (!data->forks)
	{
		printf("Malloc error\n");
		return ;
	}
	i = 0;
	while (i < data->philo_nb)
	{
		if (!mutex_option(&data->forks[i].lock, INIT))
			return ;
		data->forks[i].id = i;
		i++;
	}
	if (!init_philos(data, data->philos))
		return ;
	simulation(data, data->philos);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (valid_arguments(argc, argv) == true)
	{
		data = malloc(sizeof(t_data));
		if (!data)
		{
			printf("Malloc error\n");
			return (1);
		}
		if (!parse_data(data, argv))
		{
			free_all(data);
			return (1);
		}
		philosophers(data);
		free_all(data);
	}
	else
		arg_error();
	return (0);
}
