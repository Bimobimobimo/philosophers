/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 15:45:15 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// Dire aux philos quelles fourchettes prendre et dans quel ordre.
// philo_index = part de 0, correspond a la position du philosophe,
// alors que philo->id part de 1, c'est son numero.
static void	forks_to_philos(t_philo *philo, t_fork *forks, int philo_index)
{
	if (philo->id % 2 == 0) //pair
	{
		philo->right_fork = &forks[philo_index];
		philo->left_fork = &forks[(philo_index + 1) % philo->data->philo_nb];
	}
	else //impair
	{
		philo->left_fork = &forks[(philo_index + 1) % philo->data->philo_nb];
		philo->right_fork = &forks[philo_index];
	}	
}

bool	get_philos(t_data *data, t_philo *philos)
{
	int		i;

	i = 0;
	while (i < data->philo_nb) // initier toutes les var des struc philo
	{
		philos[i].id = i + 1;
		philos[i].meals_counter = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].finished = false;
		philos[i].died = false;
		philos[i].data = data;
		philos[i].tid = -1;
		forks_to_philos(&philos[i], data->forks, i);
		if (!mutex_option(&data->philos[i].philo_mutex, INIT, "philo_mutex")) //? pourquoi ?
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
		if (!mutex_option(&data->forks[i].fork, INIT, "fork")) // un mutex par struc fork
			return ;
		data->forks[i].fork_id = i; //l'id des fourchettes commence a 0
		i++;
	}
	if (!get_philos(data, data->philos))
		return ;
	simulation(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("Malloc error\n");
		return (1);
	}
	if (valid_arguments(argc, argv))
	{
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

/*
*
*
./philo 5	 800   200	 200 	 [5]
		nb - die - eat - sleep - [nb meals]
Logs :
(ms) (philo numero) has taken a fork
(ms) (philo numero) is eating
(ms) (philo numero) is sleeping
(ms) (philo numero) is thinking
(ms) (philo numero) died /!\ doit etre affiche dans les 10ms apres le deces
*
*
*/
