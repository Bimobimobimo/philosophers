/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/05 18:02:39 by lcollong         ###   ########.fr       */
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
	else if (philo->id % 2 == 0) //pair
	{
		philo->first_fork = &forks[philo_index];
		philo->second_fork = &forks[philo_index + 1];
	}
	else //impair
	{
		philo->first_fork = &forks[philo_index + 1];
		philo->second_fork = &forks[philo_index];
	}	
}

bool	init_philos(t_data *data, t_philo *philos)
{
	int		i;
	//debug
	t_fork *first;
	t_fork *second;
	//

	i = 0;
	while (i < data->philo_nb) // initier toutes les var des struc philo
	{
		philos[i].id = i + 1;
		// printf(YELLOW "philo numero %d initialise\n" RESET, philos[i].id); //debug
		philos[i].meals_counter = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].finished = false;
		philos[i].died = false; //? necessaire ?
		philos[i].data = data;
		philos[i].tid = -1;
		forks_to_philos(&philos[i], data->forks, i);

		//debug
		first = philos[i].first_fork;
		second = philos[i].second_fork;
		mutex_option(&data->print_lock, LOCK);
		printf(YELLOW "philo %d a fourchettes %d en 1er et %d en 2e\n" RESET, philos[i].id, first->id, second->id);
		mutex_option(&data->print_lock, UNLOCK);
		//
		
		if (!mutex_option(&data->philos[i].lock, INIT)) //? pourquoi ?
			return (false);
		i++;
	}
	return (true);	
}

void	philosophers(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->philo_nb); //autant de struc que de philos
	if (!data->philos)
	{
		printf("Malloc error\n");
		return ;
	}
	data->forks = malloc(sizeof(t_fork) * data->philo_nb); //autant de struc forks que de fourchettes (cad de philos)
	if (!data->forks)
	{
		printf("Malloc error\n");
		return ;
	}
	
	i = 0;
	while (i < data->philo_nb)
	{
		if (!mutex_option(&data->forks[i].lock, INIT)) // un mutex par struc fork
			return ;
		data->forks[i].id = i; //l'id des fourchettes commence a 0
		printf(GREEN "Fourchette numero %d creee\n" RESET, data->forks[i].id);
		i++;
	}
	if (!init_philos(data, data->philos))
		return ;
	simulation(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (valid_arguments(argc, argv))
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
		// // debogage
		// printf("\n ~ ARGUMENTS ~\n");
		// printf("philo_nb = %ld\n", data->philo_nb);
		// printf("time2die = %ld\n", data->time2die);
		// printf("time2eat = %ld\n", data->time2eat);
		// printf("time2sleep = %ld\n", data->time2sleep);
		// printf("min_meals = %ld\n", data->min_meals);
		// printf("start_time = %ld\n", data->start_time);
		// printf("the_end = %d\n", data->the_end);
		// printf("threads_ready = %d\n", data->threads_ready);
		// printf("pthread_t = %lu\n", data->monitor);
		// printf("forks = %p\n", data->forks);
		// printf("philos = %p\n\n", data->philos);

		philosophers(data);
		free_all(data);
	}
	else
		arg_error();
	return (0);
}
