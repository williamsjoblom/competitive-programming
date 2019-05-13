// William Sjöblom
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

/**
 * Point.
 */
struct Point {
    double x, y;
};


/**
 * Calculate polygon area from a list of counter clockwise ordered vertices.
 * Implemented using the shoelace formula.
 */
double area(std::vector<Point> vertices) {
    double sum = 0;
    for (int i = 0; i < vertices.size(); i++) {
        Point& v1 = vertices[i];
        Point& v2 = vertices[(i + 1) % vertices.size()];
        
        sum += v1.x*v2.y - v1.y*v2.x;
    }

    return sum / 2.0;
}


/**
 * Read 'n' vertices from stdin.
 */
std::vector<Point> scan_vertices(int n) {
    std::vector<Point> vertices;
    vertices.reserve(n);
    
    while (n--) {
        double x, y;
        std::cin >> x >> y;
        vertices.push_back({x, y});
    }

    return vertices;
}


/**
 * Entry point.
 */
int main() {
    int n;
    while (std::cin >> n) {
        if (n == 0) break;
        
        std::vector<Point> vertices = scan_vertices(n);
        double result = area(vertices);

        if (result < 0) std::cout << "CW ";
        else std::cout << "CCW ";
        
        std::cout << std::fixed << std::setprecision(1)
                  << std::abs(result)
                  << std::endl;
    }
}
