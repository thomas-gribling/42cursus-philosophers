/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:22:14 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/06 09:58:40 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put(char c)
{
	write(1, &c, 1);
}

void	*routine(void *arg)
{
	t_philo	phi;

	phi = *((t_philo *)arg);
	pthread_mutex_lock(&phi.all->write_mutex);
	printf("%04d: thread #%03d created!\n", get_time() - phi.all->start, phi.i);
	pthread_mutex_unlock(&phi.all->write_mutex);
	return (NULL);
}

void	init_philos(t_common all)
{
	t_philo	*phi;
	int		i;

	phi = malloc(all.n_philo * sizeof(t_philo));
	pthread_mutex_init(&all.write_mutex, NULL);
	i = -1;
	while (++i < all.n_philo)
	{
		phi[i].all = &all;
		phi[i].i = i;
		pthread_mutex_init(&phi[i].lf, NULL);
	}
	i = -1;
	while (++i < all.n_philo)
	{
		if (i == all.n_philo - 1)
			phi[i].rf = &phi[0].lf;
		else
			phi[i].rf = &phi[i + 1].lf;
	}
	all.start = get_time();
	i = -1;
	while (++i < all.n_philo)
		pthread_create(&phi[i].brain, NULL, routine, &phi[i]);
}

int	main(int ac, char **av)
{
	t_common	all;

	if (ac < 5 || ac > 6)
		return (1);
	all.n_philo = ft_atol(av[1]);
	all.t_die = ft_atol(av[2]);
	all.t_eat = ft_atol(av[3]);
	all.t_sleep = ft_atol(av[4]);
	if (ac == 6)
		all.n_eat = ft_atol(av[5]);
	init_philos(all);
}
