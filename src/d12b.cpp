#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <vector>

class Point
{
public:
    int32_t x = 0;
    int32_t y = 0;

    Point() {}
    Point(int32_t x, int32_t y) : x(x), y(y) {}

    std::string toString()
    {
        return std::to_string(x) + "," + std::to_string(y);
    }

    bool operator==(const Point &other) const
    {
        return x == other.x && y == other.y;
    }
};

int32_t minStepsToTop(const std::vector<std::vector<int32_t>> &heightMap, size_t width, size_t height,
                      const Point &startingPoint, const Point &endingPoint)
{
    // int32_t steps = 0;
    std::vector<std::vector<size_t>> dist(height, std::vector<size_t>(width));
    for (auto& row : dist)
        for (auto& d : row)
            d = SIZE_MAX;
    dist[startingPoint.y][startingPoint.x] = 0;

    std::queue<Point> pointQueue;
    pointQueue.push(startingPoint);
    std::unordered_set<std::string> visitedPoints;
    while (pointQueue.size() > 0) {
        Point point = pointQueue.front();
        pointQueue.pop();

        if (visitedPoints.count(point.toString()) > 0) continue;

        // std::cout << steps << " " << point.toString() << "\n";
        if (point == endingPoint) return dist[point.y][point.x];
        // steps++;
        visitedPoints.insert(point.toString());
        int32_t currentHeight = heightMap[point.y][point.x];

        //right
        if (point.x < width - 1 && 
            visitedPoints.count(Point(point.x + 1, point.y).toString()) == 0 &&
            (int32_t)heightMap[point.y][point.x + 1] - currentHeight <= 1) {
            pointQueue.push(Point(point.x + 1, point.y));
            dist[point.y][point.x + 1] = (dist[point.y][point.x + 1] < dist[point.y][point.x] + 1) ? 
                                          dist[point.y][point.x + 1] : dist[point.y][point.x] + 1;
        }
        // left
        if (point.x >= 1 && 
            visitedPoints.count(Point(point.x - 1, point.y).toString()) == 0 &&
            (int32_t)heightMap[point.y][point.x - 1] - currentHeight <= 1) {
            pointQueue.push(Point(point.x - 1, point.y));
            dist[point.y][point.x - 1] = (dist[point.y][point.x - 1] < dist[point.y][point.x] + 1) ? 
                                          dist[point.y][point.x - 1] : dist[point.y][point.x] + 1;
        }
        // "down"
        if (point.y < height - 1 && 
            visitedPoints.count(Point(point.x, point.y + 1).toString()) == 0 &&
            (int32_t)heightMap[point.y + 1][point.x] - currentHeight <= 1) {
            pointQueue.push(Point(point.x, point.y + 1));
            dist[point.y + 1][point.x] = (dist[point.y + 1][point.x] < dist[point.y][point.x] + 1) ? 
                                          dist[point.y + 1][point.x] : dist[point.y][point.x] + 1;
        }
        // "up"
        if (point.y >= 1 && 
            visitedPoints.count(Point(point.x, point.y - 1).toString()) == 0 &&
            (int32_t)heightMap[point.y - 1][point.x] - currentHeight <= 1) {
            pointQueue.push(Point(point.x, point.y - 1));
            dist[point.y - 1][point.x] = (dist[point.y - 1][point.x] < dist[point.y][point.x] + 1) ? 
                                          dist[point.y - 1][point.x] : dist[point.y][point.x] + 1;
        }
    }

    return -1;

}

int main()
{
    std::ifstream heightMapFile("inputs/d12.txt");
    std::vector<std::vector<int32_t>> heightMap = {};
    size_t row = 0;
    size_t col = 0;
    Point startingPoint;
    Point endingPoint;
    char height;

    std::vector<int32_t> currentRow;
    while (heightMapFile >> std::noskipws >> height) {
        if (height == '\n') {
            row++;
            col = 0;
            heightMap.push_back(currentRow);
            currentRow.clear();
            continue;
        }

        if (height == 'S') {
            startingPoint.x = col; 
            startingPoint.y = row;
            height = 'a';
        }

        if (height == 'E') {
            endingPoint.x = col; 
            endingPoint.y = row;
            height = 'z';
        }

        currentRow.push_back((int32_t)(height - 'a'));
        col++;
    }
    heightMap.push_back(currentRow);

    std::cout << startingPoint.toString() << " " << endingPoint.toString() << "\n";
    std::cout << "Height: " << heightMap.size() << " Width: " << heightMap[0].size() << "\n";

    int32_t minStepsNeeded = minStepsToTop(heightMap, heightMap[0].size(), heightMap.size(), 
                                           startingPoint, endingPoint);
    for (size_t r = 0; r < heightMap.size(); r++)
        for (size_t c = 0; c < heightMap[0].size(); c++) {
            if (heightMap[r][c] != 0) continue;
            int32_t stepsNeeded = minStepsToTop(heightMap, heightMap[0].size(), heightMap.size(), 
                                           Point(c, r), endingPoint);
            if (stepsNeeded == -1) continue;
            minStepsNeeded = (minStepsNeeded < stepsNeeded) ? minStepsNeeded : stepsNeeded;
        }

    std::cout << minStepsNeeded << "\n";
}