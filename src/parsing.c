/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:14:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/03/04 10:51:46 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	parse_data(t_data *data, char **argv)
{
	data->philo_nb = atol_philo(argv[1]);
	data->time2die = atol_philo(argv[2]);
	data->time2eat = atol_philo(argv[3]);
	data->time2sleep = atol_philo(argv[4]);
	if (argv[5])
		data->min_meals = atol_philo(argv[5]);
	else
		data->min_meals = -1;
	data->the_end = false;
	data->threads_ready = false;
	if (!mutex_option(&data->sim_mutex, INIT)) // mutex de la simul pour l'empecher de commencer avant que tout soit pret
		return (false);
	if (!mutex_option(&data->print_mutex, INIT))
		return (false);
	data->start_time = -1;
	data->monitor = -1;
	data->forks = NULL;
	data->philos = NULL;
	return (true);
}

bool	valid_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (false);
	while (i < argc)
	{
		if (!valid_nb(argv[i]) || atol_philo(argv[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}
