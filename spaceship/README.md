# General Approach
The SpaceShip primarily controls the ship's movement using dynamic programming. When a route is given, it keeps the speed at each vertex as a state and ultimately reconstructs the movement that results in the optimal number of turns.

When a good route can be manually determined, only dynamic programming is used. When finding a good route is difficult, a heuristic simulated annealing method is used to determine the route before applying dynamic programming.

In the simulated annealing method, the evaluation value is created based on the following indicators:

Total route length: It is obvious that a shorter route length is preferable.
The magnitude of change in the direction vector between vertices: It is better to avoid routes that significantly change the spacecraft's speed.
Since the optimal balance of these indicators varies depending on the problem, manual adjustments were made for each problem before submission.

# Files
dp: Contains the C++ program for dynamic programming
sa: Contains the program for simulated annealing
in: Contains the input cases
