#include <bits/stdc++.h>

bool isPointInsidePolygon(int px, int py, const std::vector<std::pair<int, int>>& vertices) {
    int crossings = 0, vCount = vertices.size();
    for (int i = 0; i < vCount; ++i) {
        int vx1 = vertices[i].first, vy1 = vertices[i].second;
        int vx2 = vertices[(i + 1) % vCount].first, vy2 = vertices[(i + 1) % vCount].second;
        if (((vy1 <= py) && (vy2 > py)) || ((vy2 <= py) && (vy1 > py))) {
            double intersectX = vx1 + (double)(py - vy1) * (vx2 - vx1) / (vy2 - vy1);
            if (intersectX > px) crossings++;
        }
    }
    return (crossings % 2) != 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int vertexCount;
    std::cin >> vertexCount;
    std::vector<std::pair<int, int>> polygon(vertexCount);
    int minCoordX = INT_MAX, maxCoordX = INT_MIN, minCoordY = INT_MAX, maxCoordY = INT_MIN;

    for (auto& vertex : polygon) {
        std::cin >> vertex.first >> vertex.second;
        minCoordX = std::min(minCoordX, vertex.first);
        maxCoordX = std::max(maxCoordX, vertex.first);
        minCoordY = std::min(minCoordY, vertex.second);
        maxCoordY = std::max(maxCoordY, vertex.second);
    }

    int blockSize;
    std::cin >> blockSize;

    int width = maxCoordX - minCoordX + 1, height = maxCoordY - minCoordY + 1;
    std::vector<std::vector<int>> area(height, std::vector<int>(width, 0));

    for (int y = minCoordY; y < maxCoordY; ++y) {
        for (int x = minCoordX; x < maxCoordX; ++x) {
            if (isPointInsidePolygon(x + 0.5, y + 0.5, polygon)) {
                area[y - minCoordY][x - minCoordX] = 1;
            }
        }
    }

    std::vector<std::pair<int, int>> filledCells;
    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            if (area[r][c] == 1) {
                filledCells.emplace_back(r, c);
            }
        }
    }

    std::sort(filledCells.begin(), filledCells.end());

    int minActions = INT_MAX;

    std::function<void(int, std::vector<std::vector<int>>&, int)> explore = [&](int currentIndex, std::vector<std::vector<int>>& currentGrid, int actionCount) {
        if (actionCount >= minActions) return;
        while (currentIndex < filledCells.size() && currentGrid[filledCells[currentIndex].first][filledCells[currentIndex].second] == 0) {
            currentIndex++;
        }
        if (currentIndex == filledCells.size()) {
            minActions = std::min(minActions, actionCount);
            return;
        }
        int currentY = filledCells[currentIndex].first, currentX = filledCells[currentIndex].second;
        bool canPlaceBlock = true;

        for (int dy = 0; dy < blockSize && canPlaceBlock; dy++) {
            for (int dx = 0; dx < blockSize && canPlaceBlock; dx++) {
                int newY = currentY + dy, newX = currentX + dx;
                if (newY >= height  newX >= width  currentGrid[newY][newX] == 0) {
                    canPlaceBlock = false;
                }
            }
        }

        if (canPlaceBlock) {
            std::vector<std::vector<int>> updatedGrid = currentGrid;
            for (int dy = 0; dy < blockSize; dy++) {
                for (int dx = 0; dx < blockSize; dx++) {
                    int newY = currentY + dy, newX = currentX + dx;
                    if (newY < height && newX < width) updatedGrid[newY][newX] = 0;
                }
            }
            explore(currentIndex + 1, updatedGrid, actionCount + 1);
        }
    };

    explore(0, area, 0);

    std::cout << minActions;

    return 0;
}
