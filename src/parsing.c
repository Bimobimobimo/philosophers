/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:14:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/28 16:14:46 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	parse_data(t_data *data, char **argv)
{
	data = malloc(sizeof(t_data));
	if (!data)
		return (false);
	data->philo_nb = atol_philo(argv[1]);
	data->time2die = atol_philo(argv[2]);
	data->time2eat = atol_philo(argv[3]);
	data->time2sleep = atol_philo(argv[4]);
	if (argv[5])
		data->min_meals = atol_philo(argv[5]);
	else
		data->min_meals = -1;
	data->the_end = false;

	// // debogage
	// 	printf("\n ~ ARGUMENTS ~\n");
	// 	printf("philo_nb = %ld\n", data->philo_nb);
	// 	printf("time2die = %ld\n", data->time2die);
	// 	printf("time2eat = %ld\n", data->time2eat);
	// 	printf("time2sleep = %ld\n", data->time2sleep);
	// 	printf("min_meals = %ld\n\n", data->min_meals);

	return (true);
}

bool	valid_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!valid_nb(argv[i]) || atol_philo(argv[i]) < 0)
			return (false);
		i++;
	}
	return (true);
}
