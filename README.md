# Disk Scheduler Simulator

## Overview
This project implements a disk scheduling simulator in C that models how an operating system handles disk I/O requests over time. The simulator supports multiple scheduling algorithms and computes the order of execution, total seek time, and final completion time.

The disk is modeled with the following assumptions:
- Infinite rotation speed (no rotational latency)
- Infinite data transfer rate
- Head movement cost is proportional to track distance
- Moving from track X to Y takes |X - Y| time units

---

## Implemented Algorithms

The simulator supports the following disk scheduling algorithms:

- **FCFS (First Come, First Served)**  
  Requests are served in the order they arrive.

- **SSTF (Shortest Seek Time First)**  
  Always serves the closest pending request.

- **SCAN (Elevator Algorithm)**  
  Moves in one direction, servicing requests, then reverses at the disk boundary.

- **C-SCAN (Circular SCAN)**  
  Moves in one direction only. When reaching the end, jumps to the opposite end.

- **LOOK**  
  Similar to SCAN, but only goes as far as the last request in a direction.

- **C-LOOK**  
  Similar to C-SCAN, but jumps directly between the furthest pending requests.

---

## Input Format

The program reads input from standard input:

'''
ALG N H [D]
R
t1 n1
t2 n2
...
tR nR
'''

- `ALG` → Algorithm name (FCFS, SSTF, SCAN, C-SCAN, LOOK, C-LOOK)
- `N` → Number of tracks
- `H` → Initial head position
- `D` → Initial direction (UP or DOWN, only for directional algorithms)
- `R` → Number of requests
- Each request:
  - `ti` → arrival time
  - `ni` → track number

---

## Output Format

The program prints:

1. Order of served track requests  
2. Total seek time  
3. Completion time  

Example:

55 40 60
40
45


---

## Key Concepts

- **Pending request**: A request whose arrival time has passed but has not yet been served.
- **Idle time**: If no requests are available, the system advances time to the next arrival.
- **Seek time**: Total distance traveled by the disk head.
- **Completion time**: Time when the last request is served.

---

## Implementation Details

- Requests are stored in a struct with:
  - arrival time
  - track number
  - served flag
- Simulation runs using a time-driven loop.
- Each algorithm selects the next request based on its policy.
- Head movement updates both time and total seek cost.

---

## Notes

- Tie-breaking (when needed) is done by selecting the smaller track number.
- All algorithms correctly account for:
  - waiting periods
  - head movement cost
  - dynamic arrival of requests

---

## Author

Rodrigo Molero  
University of South Florida  
Computer Engineering
