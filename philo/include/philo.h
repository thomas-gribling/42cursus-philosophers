/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/22 08:32:49 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_FORK "|% 6u % 4u      has taken a fork🍴|\n"
# define MSG_EAT "|% 6u % 4u             is eating🍝|\n"
# define MSG_SLEEP "|% 6u % 4u           is sleeping😴|\n"
# define MSG_THINK "|% 6u % 4u           is thinking🧠|\n"
# define MSG_DIE "|% 6u % 4u                  died💀|\n"

typedef struct s_common
{
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	long			n_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	unsigned int	start;
	int				dead;
}					t_common;

typedef struct s_philo
{
	int				i;
	unsigned int	start;
	unsigned int	last_eat;
	unsigned int	meals_left;
	pthread_t		brain;
	pthread_t		death_check;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	lf;
	pthread_mutex_t	*rf;
	t_common		*all;
}					t_philo;

void			init_philos(t_common *all);
void			philo_eat(t_philo *phi);

void			put_message(char *msg, t_philo *phi);
void			put_msg_quick(char *msg, unsigned int time, int i);
unsigned int	get_time(void);
void			ft_usleep(unsigned int ms);
void			free_philos(t_philo **phi);

long			ft_atol(char *s);
int				ft_strcmp(char *s1, char *s2);
int				ft_min(int a, int b);
int				is_num(char *s);
int				ft_strlen(char *s);

#endif