<h1 align="center">
        philosophers
</h1>

<p align="center">
        <i>42 cursus - Rank 3</i><br>
        Final grade: <b>100/100</b>
</p>

# 📝 Subject
This project consists in coding a simulation with threads and mutexes of philosophers complying to the rules given in arguments:
- numbers_of_philos
- time_to_die
- time_to_eat
- time_to_sleep
- number_of_meals *(optional)*

The philosophers are sitting around a table with a plate of spaghetti in the middle. There is also one fork between each philosopher. In order to eat, a philosopher must takes the fork at his right, and the one at his left, which means two neighbours can't eat at the same time.
After eating for `time_to_eat` milliseconds, they drop their forks and sleep for `time_to_sleep` ms, then they start to think while waiting for the forks to be available again. They must eat, sleep and eat again in less than `time_to_die` ms, else they die (logic).
Also, every philosopher will spawn with one fork, which means that if there's only one, his fate is to take his only fork and wait for his death.

Here's an example of simulation:
```
tgriblin42% ./philo 2 1000 100 100 2
 ___________________________________
|__TIME___ID______ACTION____________|
|     0    1      has taken a fork🍴|
|     0    1      has taken a fork🍴|
|     0    1             is eating🍝|
|   100    1           is sleeping😴|
|   100    2      has taken a fork🍴|
|   100    2      has taken a fork🍴|
|   100    2             is eating🍝|
|   200    1           is thinking🧠|
|   200    1      has taken a fork🍴|
|   200    1      has taken a fork🍴|
|   200    1             is eating🍝|
|   200    2           is sleeping😴|
|   300    2           is thinking🧠|
|   300    2      has taken a fork🍴|
|   300    2      has taken a fork🍴|
|   300    2             is eating🍝|
|___________________________________|
```
The simulation ended after every philosopher ate twice.

# 🖥️ Usage
To compile the project, you simply need to type `make` in the `philo/` directory in your shell terminal.<br>
You will get a `philo` executable.

Give the arguments as following:
```bash
./philo numbers_of_philo time_to_die time_to_eat time_to_sleep [numbers_of_meals]
```
