# Philosophers

An implementation of the classic Dining Philosophers problem in C using threads and mutexes.

## Overview

The Dining Philosophers problem is a classic example of synchronization issues in computer science. A certain number of philosophers sit at a round table. Each philosopher needs two forks to eat. Between each pair of philosophers lies one fork. The philosophers spend their time thinking and eating. To eat, they must pick up both adjacent forks. After eating, they put the forks down and think.

The challenge is to develop an algorithm that:
- Prevents deadlocks (when all philosophers pick up one fork and wait for the second)
- Prevents starvation of individual philosophers
- Ensures efficient resource utilization

## Key Learnings

- **Thread Management**: Creating, synchronizing, and terminating threads
- **Mutex Locks**: Safe handling of shared resources
- **Race Conditions**: Identifying and avoiding race conditions
- **Deadlock Prevention**: Strategies to prevent deadlocks
- **Resource Synchronization**: Coordination of multiple parallel processes
- **Time Measurement**: Precise time measurement in milliseconds
- **Memory Management**: Clean allocation and deallocation of resources

### File Structure

```bash
philosophers/
├── Makefile
├── includes/
│   └── philosophers.h
└── src/
    ├── main.c
    ├── init.c
    ├── utils.c
    └── monitoring.c

```

## Usage

### Compilation

```bash
make
```

### Running the Program

```bash
./philo 5 800 200 200 7
```

This starts a simulation with:
- 5 philosophers
- 800ms survival time without eating
- 200ms eating time
- 200ms sleeping time
- 7 meals per philosopher

### Cleanup

```bash
make clean    # Removes object files
make fclean   # Removes object files and executable
make re       # Rebuilds the project
```

### License

This project is part of the 42 School curriculum.
