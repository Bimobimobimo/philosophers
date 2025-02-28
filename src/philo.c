/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/28 17:25:33 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	forks_to_philos(t_philo *philo, t_fork *forks, int i)
{
	/* DEADLOCK : si chacun prend la fourchette de droite ou gauche */
	
	philo->left_fork = forks + i; // = philo->id
	if (i == 0)
		philo->right_fork = forks + (philo->data->philo_nb - 1);
	else
		philo->right_fork = forks + (i - 1); // = philo->id - 1
}

bool	get_philos(t_data *data)
{
	int		i;
	t_philo	*philo;
	
	i = 0;
	while (i < data->philo_nb)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->meals_counter = 0;
		philo->finished = false;
		// philo->last_meal_time = 0;
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
	data->forks = malloc(sizeof(t_fork));
	if (!data->forks)
	{
		printf("Malloc error\n");
		return ;
	}
	while (i < data->philo_nb)
	{
		if (!mutex_action(&data->forks[i].fork, INIT))
			return ;
		data->forks[i].fork_id = i;
		i++;
	}
	if (!get_philos(data))
		return ;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if ((argc == 5 || argc == 6) && valid_arguments(argc, argv))
	{
		if (!parse_data(&data, argv))
		{
			printf("Malloc error\n");
			free_data(&data);
			return (1);
		}
		philosophers(&data);
		free_data(&data);
	}
	else
		arg_error();
	return (0);
}

/*
./philo 5 800 200 200 [5]

Logs :
(ms) (philo numero) has taken a fork
(ms) (philo numero) is eating
(ms) (philo numero) is sleeping
(ms) (philo numero) is thinking
(ms) (philo numero) died /!\ doit etre affiche dans les 10ms apres le deces

/!\ pas de data race.

*/
