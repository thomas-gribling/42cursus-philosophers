/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 08:41:42 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/23 08:42:20 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_threads(t_philo **phi, t_common *all)
{
	int	i;

	i = -1;
	while (++i < (int)all->n_philo)
	{
		if (i == (int)all->n_philo - 1)
			phi[i]->rf = &phi[0]->lf;
		else
			phi[i]->rf = &phi[i + 1]->lf;
		phi[i]->start = get_time();
		pthread_create(&phi[i]->brain, NULL, routine, phi[i]);
	}
	i = -1;
	while (++i < (int)all->n_philo)
		pthread_join(phi[i]->brain, NULL);
}

void	init_philos(t_common *all)
{
	t_philo	**phi;
	int		i;

	phi = malloc((all->n_philo + 1) * sizeof(t_philo *));
	pthread_mutex_init(&all->write_mutex, NULL);
	pthread_mutex_init(&all->death_mutex, NULL);
	i = -1;
	while (++i < (int)all->n_philo)
	{
		phi[i] = malloc(sizeof(t_philo));
		phi[i]->all = all;
		phi[i]->i = i;
		phi[i]->meals_left = all->n_eat;
		pthread_mutex_init(&phi[i]->eat_mutex, NULL);
		pthread_mutex_init(&phi[i]->lf, NULL);
	}
	phi[i] = NULL;
	init_threads(phi, all);
	free_philos(phi);
}
