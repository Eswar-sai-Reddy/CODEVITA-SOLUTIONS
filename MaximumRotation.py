def rl(layer, pos, dir, ol):
    n = len(layer)
    rot = [None] * n


    if dir == "clockwise":
        for i in range(n):
            rot[(i + pos) % n] = layer[i]
    else:
        for i in range(n):
            rot[(i - pos) % n] = layer[i]

    for i in range(n):
        if ol:
            rot[i] = chr(((ord(rot[i]) - ord('A') - 1) % 26) + ord('A'))
        else:
            rot[i] = chr(((ord(rot[i]) - ord('A') + 1) % 26) + ord('A'))


    return rot


def aq(pl, row, col, size):
    layers = []
    for layer in range(size // 2):
        cl = []
        for j in range(col + layer, col + size - layer):
            cl.append(pl[row + layer][j])
        for i in range(row + layer + 1, row + size - layer - 1):
            cl.append(pl[i][col + size - layer - 1])
        for j in range(col + size - layer - 1, col + layer - 1, -1):
            cl.append(pl[row + size - layer - 1][j])
        for i in range(row + size - layer - 2, row + layer, -1):
            cl.append(pl[i][col + layer])


        layers.append(cl)

    for lidx, layer in enumerate(layers):
        ol = (lidx + 1) % 2 == 1
        dir = "counterclockwise" if ol else "clockwise"
        pos = lidx + 1
        rotated_layer = rl(layer, pos, dir, ol)

        idx = 0
        for j in range(col + lidx, col + size - lidx):
            pl[row + lidx][j] = rotated_layer[idx]
            idx += 1
        for i in range(row + lidx + 1, row + size - lidx - 1):
            pl[i][col + size - lidx - 1] = rotated_layer[idx]
            idx += 1
        for j in range(col + size - lidx - 1, col + lidx - 1, -1):
            pl[row + size - lidx - 1][j] = rotated_layer[idx]
            idx += 1
        for i in range(row + size - lidx - 2, row + lidx, -1):
            pl[i][col + lidx] = rotated_layer[idx]
            idx += 1



def placementlelo(n, pl, queries):
    for row, col, size in queries:
        aq(pl, row, col, size)
    result = ''.join(''.join(row) for row in pl)
    return result



n = int(input())
pl = [list(input().strip().split()) for _ in range(n)]
q = int(input().strip())
queries = [tuple(map(int, input().strip().split())) for _ in range(q)]

result = placementlelo(n, pl, queries)
print(result, end="")
