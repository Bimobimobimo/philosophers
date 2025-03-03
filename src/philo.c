/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/03 13:57:40 by lcollong         ###   ########.fr       */
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

bool	get_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_nb) // initier toutes les var des struc philo
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->finished = false;
		// philo->tid = 0;
		philo->data = data;
		forks_to_philos(philo, data->forks, i);
		i++;
	}
	return (true);	
}

void	philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo));
	if (!data->philos)
	{
		printf("Malloc error\n");
		return ;
	}
	if (!mutex_action(&data->sim_mutex, INIT)) // pourquoi ?
		return ;
	data->forks = malloc(sizeof(t_fork));
	if (!data->forks)
	{
		printf("Malloc error\n");
		return ;
	}
	while (i < data->philo_nb)
	{
		if (!mutex_action(&data->forks[i].fork, INIT)) // un mutex par struc fork
			return ;
		data->forks[i].fork_id = i;
		i++;
	}
	if (!get_philos(data))
		return ;
	simulation(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (valid_arguments(argc, argv))
	{
		if (!parse_data(&data, argv))
		{
			free_all(&data);
			return (1);
		}
		philosophers(&data);
		free_all(&data);
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
