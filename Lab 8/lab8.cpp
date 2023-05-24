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
            if (point.y == line.k * point.x + line.b || std::isnan(line.k)) {
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

void backtrack(const std::vector<Point>& points, std::vector<Line>& lines, std::vector<Line>& bestLines, std::vector<bool>& used) {
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
            if (!used[j])
            {
                Line tmp;
                if (points[i].x == points[j].x)
                {
                    tmp.k = NAN;
                    tmp.b = points[i].x;
                }
                else
                {
                    tmp.k = (points[j].y - points[i].y) / (points[j].x - points[i].x);
                    tmp.b = points[i].y - tmp.k * points[i].x;
                }
                
                used[j] = true;
                lines.push_back(tmp);
                backtrack(points, lines, bestLines, used);
                lines.pop_back();
                used[j] = false;
            }
        }
    }
}

int main() {
    std::vector<Point> points = { {1, 1}, {1, 7}/*, {7, 1}, {4, 4}*/ };
    std::vector<Line> lines;
    std::vector<Line> bestLines(points.size());
    std::vector<bool> used(points.size(), false);
    backtrack(points, lines, bestLines, used);
    std::cout << "Minimum set of lines: ";
    for (const auto& line : bestLines) {
        if (std::isnan(line.k)) { // для вертикальных прямых выводим отдельное сообщение
            std::cout << "x = " << line.b << "; ";
        }
        else {
            std::cout << "y = " << line.k << "x + " << line.b << "; ";
        }
    }
    std::cout << std::endl;
    return 0;
}
