# Philosophers

## Description
The Philosophers project is a simulation of the classic "Dining Philosophers" problem. The goal of the project is to implement a solution for synchronizing multiple threads (philosophers) who need to share limited resources (forks) to eat. The challenge lies in preventing deadlock and ensuring that the philosophers can eat and think without interference, using mutexes.

## Features
- Simulates the behavior of philosophers sitting at a table with two forks each.
- Each philosopher alternates between thinking and eating.
- The project requires the use of pthread for managing threads and mutexes for synchronizing access to the forks.
- Prevents deadlock and starvation by ensuring that philosophers can eat in a fair and efficient manner.
- 
## Prerequisites
- C Compiler: The project should be compiled using gcc with the default flags (e.g., `-Wall -Wextra -Werror`).
- pthread: The project requires the use of the pthread library to manage threads.

## Installation
Clone the repository:
```bash
git clone https://github.com/your-username/philosophers.git
```
Navigate to the project directory:
```bash
cd philosophers
```
Compile the project:
```bash
make
```

## Usage
To run the simulation, execute the compiled program with the desired number of philosophers and the time they will spend eating or thinking:

```bash
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> <optional_number_of_meals>
```

Example:
```bash
$ ./philosophers 5 800 200 200
```

In this example:
- `5` is the number of philosophers.
- `800` is the time in milliseconds before a philosopher dies if they haven't eaten.
- `200` is the time in milliseconds a philosopher spends eating and sleeping.

## Parameters
- `<number_of_philosophers>`: The number of philosophers to simulate.
- `<time_to_die>`: The time in milliseconds before a philosopher dies if they haven’t eaten.
- `<time_to_eat>`: The time in milliseconds that a philosopher spends eating.
- `<time_to_sleep>`: The time in milliseconds that a philosopher spends sleeping.
- `<optional_number_of_meals>`: (Optional) The number of meals each philosopher must eat before the simulation ends. If not provided, philosophers will eat indefinitely until they die.

## Logic and Requirements
- Philosophers must be able to think, eat, and sleep.
- Each philosopher needs two forks to eat.
- The program should prevent deadlock (where no philosopher can eat) and ensure that all philosophers get a chance to eat.
- A philosopher should be allowed to eat only if they can acquire both forks at the same time.
