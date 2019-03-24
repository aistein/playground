#!/usr/local/bin/python3

class Solution:
    def explore(self, i, j, grid, explored):
        from collections import deque
        S = deque([(i,j)]) # DFS Stack
        m, n = len(grid), len(grid[0])
        while len(S) > 0:
            # print(S)
            i, j = S[-1] # "peek" top of stack
            explored[i][j] = True # prevent 'all-directions' traversal loops
            # Check Bottom
            if i+1 < m:
                if not explored[i+1][j] and grid[i+1][j] == '1':
                    # print("exploring bottom")
                    S.append((i+1,j))
                    continue
            # Check Left
            if j-1 >= 0:
                if not explored[i][j-1] and grid[i][j-1] == '1':
                    # print("exploring left")
                    S.append((i,j-1))
                    continue
            # Check Right
            if j+1 < n:
                if not explored[i][j+1] and grid[i][j+1] == '1':
                    # print("exploring right")
                    S.append((i,j+1))
                    continue
            # Check Top
            if i-1 >= 0:
                if not explored[i-1][j] and grid[i-1][j] == '1':
                    # print("exploring top")
                    S.append((i-1,j))
                    continue
            # Nothing left to Explore from current position
            # print("done exploring: {}".format(S[-1]))
            S.pop()
        return
    def numIslands(self, grid):
        if len(grid) == 0:
            return 0
        n, m = len(grid[0]), len(grid)
        explored = [[False for _ in range(n)] for _ in range(m)]
        i, j, island_cnt = 0, 0, 0 # i- row, j- col
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '1' and explored[i][j] == False:
                    # mutable objects are passed as references
                    self.explore(i, j, grid, explored)
                    island_cnt += 1
        return island_cnt
        


s = Solution()
test1 = [["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]
print(s.numIslands(test1))
test2 = [["1","1","0","0","0"],["1","1","0","0","0"],["0","0","1","0","0"],["0","0","0","1","1"]]
print(s.numIslands(test2))