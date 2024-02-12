/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:06:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/12 16:14:48 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die(t_philo *phi)
{
	pthread_mutex_lock(&phi->all->death_mutex);
	phi->all->dead = 1;
	put_message(MSG_DIE, phi);
}

void	*check_death(void *arg)
{
	t_philo	*phi;

	phi = (t_philo *)arg;
	while (!phi->all->dead)
		if (!phi->eating)
			if (get_time() - phi->last_eat >= phi->all->t_die)
				die(phi);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*phi;
	pthread_t		death_check;

	phi = (t_philo *)arg;
	phi->last_eat = phi->all->start;
	if (phi->i % 2)
		ft_usleep(ft_min(phi->all->t_die, phi->all->t_eat / 2));
	pthread_create(&death_check, NULL, check_death, phi);
	while (!phi->all->dead)
	{
		if (phi->all->dead)
			return (NULL);
		if (philo_start_eating(phi))
			return (NULL);
		ft_usleep(phi->all->t_eat);
		phi->last_eat = get_time();
		if (philo_start_sleeping(phi))
			return (NULL);
		ft_usleep(ft_min(phi->all->t_die, phi->all->t_sleep));
		if (phi->all->dead)
			return (NULL);
		put_message(MSG_THINK, phi);
	}
	return (NULL);
}

void	init_philos(t_common *all)
{
	t_philo	**phi;
	int		i;

	phi = malloc(all->n_philo * sizeof(t_philo *));
	i = -1;
	while (++i < all->n_philo)
	{
		phi[i] = malloc(sizeof(t_philo));
		phi[i]->all = all;
		phi[i]->i = i;
		phi[i]->eating = 0;
		phi[i]->meals_left = all->n_eat;
		pthread_mutex_init(&phi[i]->lf, NULL);
	}
	i = -1;
	while (++i < all->n_philo)
	{
		if (i == all->n_philo - 1)
			phi[i]->rf = &phi[0]->lf;
		else
			phi[i]->rf = &phi[i + 1]->lf;
	}
	all->start = get_time();
	i = -1;
	while (++i < all->n_philo)
		pthread_create(&phi[i]->brain, NULL, routine, phi[i]);
	i = -1;
	while (++i < all->n_philo)
		pthread_join(phi[i]->brain, NULL);
}
