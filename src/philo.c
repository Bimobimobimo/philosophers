/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:02:22 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/27 15:52:46 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitoring(void *ptr)
{
	t_data	*data;

	data = (t_data *)ptr;
	(void)data;
	printf("Monitoring thread routine...\n");
	//if one philo dies : stops everything
	//else if all philo ate min_meals : stops everything
	return (NULL);
}

void	*philo_routine(void *ptr)
{
	t_data *data;
	
	data = (t_data *)ptr;
	(void)data;
	printf("Philo thread routine...\n");
/* 	while (data->philo->is_dead == false)
	{
		//printf philo_num has taken a fork
		//locks l_fork
		//printf philo_num has taken a fork
		//locks r_fork
		//printf philo_num is eating
		//eat : usleep(args->time2eat)
		//unlocks r_fork
		//unlocks l_fork
		//printf philo_num is sleeping
		//sleep : usleep(args->time2sleep)
		//printf philo_num is thinking
		//think : usleep(args->time2think)
	} */
	return (NULL);
}

void	join_threads(pthread_t *philo)
{
	pthread_join(*philo, NULL);
	printf("Thread [%ld] joined.\n\n", *philo);
}

pthread_t	create_threads(void)
{
	pthread_t	philo;

	if (pthread_create(&philo, NULL, philo_routine, NULL) != 0)
		return (EXIT_FAILURE);
	printf("Thread [%ld] created.\n", philo);
	return (philo);
}

void	philosophers(t_data *data)
{
	// pthread_t	monitor;
	// t_philo		*tmp;
	// int	i;

	// //create all mutexes
	// init_mutexes(data->locks);
	
	// //create monitoring thread
	// pthread_create(&monitor, NULL, monitoring, data);

	data->philo = create_philo_list(data);

	// //create all philo threads
	// i = 0;
	// tmp = data->philo;
	// while (i < data->nb)
	// {
	// 	tmp->td = create_threads();
	// 	tmp->philo_num = i + 1;
	// 	free(tmp);
	// 	tmp = data->philo->next;
	// 	i++;
	// }
	// i = 0;
	// while (i < data->nb)
	// {
	// 	join_threads(&data->philo->td);
	// 	i++;
	// }

	// // destroy all mutexes
	// destroy_mutexes(data->locks);
	
	free_data_list(data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if ((argc == 5 || argc == 6) && is_positive_nb(argc, argv) == true)
	{
		data = get_data(argv);
		// printf("\033[32mArguments OK\n\n\033[0m");
		philosophers(&data);
	}
	else
	{
		printf("\033[1mArgument error, retry with : \033[31;0m./philo ");
		printf("\033[38;2;255;165;0mNumber_of_philosophers ");
		printf("\033[31mTime_to_die \033[38;2;255;165;0mTime_to_eat ");
		printf("\033[31mTime_to_sleep \033[0mand optionally");
		printf("\033[38;2;255;165;0m Number_of_time_each_");
		printf("philosopher_must_eat\n\033[0m");
	}
	return (0);
}

/*

Logs :
(ms) (philo numero) has taken a fork
(ms) (philo numero) is eating
(ms) (philo numero) is sleeping
(ms) (philo numero) is thinking
(ms) (philo numero) died /!\ doit etre affiche dans les 10ms apres le deces

/!\ pas de data race.

*/
