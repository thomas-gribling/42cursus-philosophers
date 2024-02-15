/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 09:06:36 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/15 08:37:27 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	die(t_philo *phi)
{
	if (phi->all->dead)
		return ;
	pthread_mutex_lock(&phi->all->death_mutex);
	phi->all->dead++;
	put_message(MSG_DIE, phi);
	pthread_mutex_unlock(&phi->all->death_mutex);
}

void	*check_death(void *arg)
{
	t_philo	*phi;

	if (!arg)
		return (NULL);
	phi = (t_philo *)arg;
	ft_usleep(phi->all->t_die + 1);
	if (phi->eating)
		return (NULL);
	if (get_time() - phi->last_eat >= phi->all->t_die)
		die(phi);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo			*phi;

	phi = (t_philo *)arg;
	phi->last_eat = phi->all->start;
	if (phi->i % 2)
		ft_usleep(ft_min(phi->all->t_die, phi->all->t_eat));
	while (!phi->all->dead)
	{
		philo_eat(phi);
		if (!phi->meals_left)
			break;
		pthread_create(&phi->death_check, NULL, check_death, phi);
		put_message(MSG_SLEEP, phi);
		ft_usleep(phi->all->t_sleep);
		put_message(MSG_THINK, phi);
		pthread_detach(phi->death_check);
	}
	return (NULL);
}

void	init_threads(t_philo **phi, t_common *all)
{
	int			i;

	i = -1;
	while (++i < (int)all->n_philo)
	{
		if (i == (int)all->n_philo - 1)
			phi[i]->rf = &phi[0]->lf;
		else
			phi[i]->rf = &phi[i + 1]->lf;
	}
	all->start = get_time();
	i = -1;
	while (++i < (int)all->n_philo)
		pthread_create(&phi[i]->brain, NULL, routine, phi[i]);
	i = -1;
	while (++i < (int)all->n_philo)
		pthread_join(phi[i]->brain, NULL);
}

void	init_philos(t_common *all)
{
	t_philo	**phi;
	int		i;

	phi = malloc((all->n_philo + 1) * sizeof(t_philo *));
	i = -1;
	while (++i < (int)all->n_philo)
	{
		phi[i] = malloc(sizeof(t_philo));
		phi[i]->all = all;
		phi[i]->i = i;
		phi[i]->eating = 0;
		phi[i]->meals_left = all->n_eat;
	}
	phi[i] = NULL;
	i = -1;
	while (++i)
		pthread_mutex_init(&phi[i]->lf, NULL);
	init_threads(phi, all);
	free_philos(phi);
}
