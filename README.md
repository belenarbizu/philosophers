This project involves simulating the dining philosophers problem with threads and mutexes.<br/>
The program use threads to represent each philosopher, and each philosopher has a fork to their left and right.<br/>
The program simulates philosophers sitting around a table, each with a fork. The key challenge is to prevent philosophers from using the same fork simultaneously, which is done by protecting each fork's state with a mutex.<br/>
Philosophers alternately think, eat, and sleep, but they can only eat if they have both forks.<br/>
Philosophers must avoid dying, which happens if they go without eating for too long.<br/>
<br/>
Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat] <br/>
The simulation runs until a philosopher dies or, if specified, when all philosophers have eaten the required number of times.<br/>
The program outputs logs for each state change of a philosopher, ensuring precise timestamps.<br/>
