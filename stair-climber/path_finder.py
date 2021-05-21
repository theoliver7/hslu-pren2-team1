import numpy as np
from pathfinding.core.diagonal_movement import DiagonalMovement
from pathfinding.core.grid import Grid
from pathfinding.finder.a_star import AStarFinder


class Pathfinder():
    # Matrix for testing
    matrix = [
        [1, 1, 1, 1, 1, 1, 1, 1],  # Top Platform
        [1, 1, 1, 1, 1, 1, 1, 1],
        [1, 1, 0, 0, 0, 1, 1, 1],
        [1, 1, 1, 1, 0, 1, 1, 1],
        [1, 1, 1, 1, 1, 0, 0, 0],
        [0, 0, 1, 1, 1, 0, 1, 1],
        [1, 1, 1, 1, 1, 1, 1, 1]  # Floor
    ]

    def compute_path(self, matrix):
        grid = Grid(matrix=matrix)

        start = grid.node(0, 6)
        end = grid.node(5, 0)

        finder = AStarFinder(diagonal_movement=DiagonalMovement.never)
        path, runs = finder.find_path(start, end, grid)

        print('operations:', runs, 'path length:', len(path))
        print(grid.grid_str(path=path, start=start, end=end))

        return path
