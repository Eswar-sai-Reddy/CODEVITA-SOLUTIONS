from collections import deque

def count_infected_neighbors(board, x, y):
    size = len(board)
    infected_count = 0
    for dx in [-1, 0, 1]:
        for dy in [-1, 0, 1]:
            if dx == 0 and dy == 0:
                continue
            nx, ny = x + dx, y + dy
            if 0 <= nx < size and 0 <= ny < size and board[nx][ny] == 1:
                infected_count += 1
    return infected_count

def plague_simulation(board):
    size = len(board)
    new_board = [row[:] for row in board]
    
    for x in range(size):
        for y in range(size):
            infected_count = count_infected_neighbors(board, x, y)
            if board[x][y] == 0 and infected_count == 3:
                new_board[x][y] = 1
            elif board[x][y] == 1 and (infected_count < 2 or infected_count > 3):
                new_board[x][y] = 0
                
    return new_board

def find_path(grid_size, initial_board):
    board = [[1 if cell == '1' else 0 for cell in row] for row in initial_board]
    start_x, start_y, end_x, end_y = -1, -1, -1, -1
    
    for x in range(grid_size):
        for y in range(grid_size):
            if initial_board[x][y] == 's':
                start_x, start_y = x, y
                board[x][y] = 0
            if initial_board[x][y] == 'd':
                end_x, end_y = x, y
                board[x][y] = 0
    
    queue = deque([(start_x, start_y, board, 0)])
    visited_states = set()
    
    while queue:
        x, y, current_board, days = queue.popleft()
        
        if x == end_x and y == end_y:
            return days
        
        state = (x, y, tuple(map(tuple, current_board)))
        if state in visited_states:
            continue
        visited_states.add(state)
        
        next_board = plague_simulation(current_board)
        for dx, dy in [(0, 0), (-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < grid_size and 0 <= ny < grid_size and next_board[nx][ny] == 0:
                queue.append((nx, ny, next_board, days + 1))
    
    return -1

if name == "main":
    n = int(input())
    grid = [input().strip() for _ in range(n)]
    print(find_path(n, grid) + 1)
