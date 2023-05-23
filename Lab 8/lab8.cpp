#include <iostream>
#include <vector>
#include <algorithm>

struct Line
{
    double k = 0;
    double b = 0;
};

struct Point {
    double x, y;
};

bool isCovered(const std::vector<Point>& points, const std::vector<Line>& lines) {
    for (const auto& point : points) {
        bool covered = false;
        for (const auto& line : lines) {
            if (point.y == line.k * point.x + line.b) {
                covered = true;
                break;
            }
        }
        if (!covered) {
            return false;
        }
    }
    return true;
}

void backtrack(const std::vector<Point>& points, std::vector<Line>& lines, std::vector<Line>& bestLines) {
    if (isCovered(points, lines)) {
        if (lines.size() < bestLines.size()) {
            bestLines = lines;
        }
        return;
    }
    if (lines.size() >= bestLines.size())
        return;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            if (points[i].x != points[j].x) 
            {
                Line tmp;
                tmp.k = (points[j].y - points[i].y) / (points[j].x - points[i].x);
                tmp.b = points[i].y - tmp.k * points[i].x;
                lines.push_back(tmp);
                backtrack(points, lines, bestLines);
                lines.pop_back();
            }
        }
    }
}

int main() {
    std::vector<Point> points = { {1, 1}, {1, 3}/*, {-1, 1}, {-1, -1}*/ };
    std::vector<Line> lines;
    std::vector<Line> bestLines(points.size());
    backtrack(points, lines, bestLines);
    std::cout << "Minimum set of lines: ";
    for (const auto& line : bestLines) {
        std::cout << "y = " << line.k << "x + " << line.b << "; ";
    }
    std::cout << std::endl;
    return 0;
}
