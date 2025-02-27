/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcollong <lcollong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:14:59 by lcollong          #+#    #+#             */
/*   Updated: 2025/02/27 15:54:29 by lcollong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_data	get_data(char **argv)
{
	t_data	data;

	data.nb = ft_atoi(argv[1]);
	data.time2die = ft_atoi(argv[2]);
	data.time2eat = ft_atoi(argv[3]);
	data.time2sleep = ft_atoi(argv[4]);
	if (argv[5])
		data.min_meals = ft_atoi(argv[5]);
	else
		data.min_meals = -1;
	data.philo = NULL;
	data.locks = NULL;
	
// // debogage
// 	printf("data.nb %d\n", data.nb);
// 	printf("data.time2die %d\n", data.time2die);
// 	printf("data.time2eat %d\n", data.time2eat);
// 	printf("data.time2sleep %d\n", data.time2sleep);
// 	printf("data.min_meals %d\n", data.min_meals);
// 	printf("")
	
	return (data);
}

t_philo	*get_last_node(t_philo *philo)
{
	if (!philo)
		return (NULL);
	while (philo->next)
		philo = philo->next;
	return (philo);
}

t_philo	**create_philo_list(t_data *data)
{
	t_philo	**philo;
	t_philo	*new;
	int		i;

	philo = NULL;
	i = 0;
	while (i < data->nb)
	{
		new = create_philo_node(data);
		if (!new)
			return NULL;
		new->philo_num = i - 1;
		if (philo && new)
		{
			if (*philo == NULL)
				*philo = new;
			else
				get_last_node(*philo)->next = new;
			free(new);
		}
		i++;
	}
	//debug
	while (*philo)
	{
		printf("Philo numero %d\n", (*philo)->philo_num);
		*philo = (*philo)->next;
	}
	return (philo);
}

t_philo	*create_philo_node(t_data *data)
{
	t_philo	*philo;

	(void)data;
	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->is_dead = false;
	philo->nb_of_meals = 0;
	philo->td = 0;
	philo->philo_num = 0;
	philo->next = NULL;
	return (philo);
}

void	free_data_list(t_data *data)
{
	if (data->philo)
		free_philo_list(data->philo);
	if (data)
	{
		free(data);
		data = NULL;
	}
}

void	free_philo_list(t_philo **philo)
{
	t_philo *current;
	t_philo	*previous;
	
	current = *philo;
	while (current)
	{
		previous = current;
		current = current->next;
		if (previous)
			free(previous);
	}
	if (philo)
	{
		free(philo);
		philo = NULL;
	}	
}
