from collections import deque
import itertools

def get_shortest_path(grid, N):
    start = None
    end = None
    for i in range(N):
        for j in range(N):
            if grid[i][j] == 'S':
                start = (i, j)
            elif grid[i][j] == 'D':
                end = (i, j)

    queue = deque([(start, 0)])
    visited = {start}

    while queue:
        (x, y), dist = queue.popleft()
        if grid[x][y] == 'D':
            return dist

        for nx, ny in [(x+1, y), (x-1, y), (x, y+1), (x, y-1)]:
            if 0 <= nx < N and 0 <= ny < N and (nx, ny) not in visited and grid[nx][ny] != 'T':
                visited.add((nx, ny))
                queue.append(((nx, ny), dist + 1))
    return float('inf')

def get_sheets(grid, N, M):
    sheets = []
    for i in range(0, N, M):
        for j in range(0, N, M):
            sheet = []
            for x in range(M):
                row = []
                for y in range(M):
                    row.append(grid[i+x][j+y])
                sheet.append(row)
            sheets.append(sheet)
    return sheets

def make_grid(arrangement, sheets, N, M):
    grid = [["" for _ in range(N)] for _ in range(N)]
    num_sheets = N // M

    for idx, sheet_idx in enumerate(arrangement):
        sheet = sheets[sheet_idx]
        base_i = (idx // num_sheets) * M
        base_j = (idx % num_sheets) * M

        for i in range(M):
            for j in range(M):
                grid[base_i + i][base_j + j] = sheet[i][j]
    return grid

def solve():
    N, M = map(int, input().split())
    original_grid = []
    for _ in range(N):
        original_grid.append(list(input().strip()))

    sheets = get_sheets(original_grid, N, M)
    num_sheets = (N // M) ** 2

    s_sheet = d_sheet = None
    for i, sheet in enumerate(sheets):
        for row in sheet:
            if 'S' in row:
                s_sheet = i
            if 'D' in row:
                d_sheet = i

    min_dist = float('inf')
    nums = list(range(num_sheets))
    nums.remove(s_sheet)
    nums.remove(d_sheet)

    for middle_perm in itertools.permutations(nums):
        arrangement = [s_sheet] + list(middle_perm) + [d_sheet]
        grid = make_grid(arrangement, sheets, N, M)
        min_dist = min(min_dist, get_shortest_path(grid, N))

    return min_dist

if name == "main":
    print(solve())
