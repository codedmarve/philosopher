/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moduwole <moduwole@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:03:22 by moduwole          #+#    #+#             */
/*   Updated: 2023/01/12 16:03:22 by moduwole         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;
	t_philo	*phi;

	if (!checks(argc, argv))
		return (1);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: memory allocation failed\n"), 2);
	if (!init_data(data, argv, argc))
		return (3);
	phi = malloc(sizeof(t_philo) * (data->n_philo + 1));
	if (!phi)
		return (printf("Error: memory allocation failed\n"), 4);
	init_philo(phi, data);
	if (data->n_philo == 1)
	{
		one_philo(data, phi);
		return (0);
	}
	if (!th_create(phi))
		return (6);
	free_all(data, phi);
	return (0);
}

void	one_philo(t_data *data, t_philo *phi)
{
	data->time = get_time();
	state_print(phi, 1, GREEN, FORK);
	time_sim(data->t_die);
	state_print(phi, 1, RED, DIED);
	free_all(data, phi);
}
