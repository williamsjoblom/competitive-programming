// William Sjöblom
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>

/**
 * 2D point.
 */
struct Point {
    double x, y;

    /**
     * Addition.
     */
    Point operator+(Point p) {
        return {x + p.x, y + p.y};        
    }

    
    /**
     * Subtraction.
     */
    Point operator-(Point p) {
        return {x - p.x, y - p.y};
    }

    
    /**
     * Negation.
     */
    Point operator-() {
        return { -x, -y };
    }

    
    /**
     * Multiplication.
     */
    Point operator*(double d) {
        return { x*d, y*d };
    }

    
    /**
     * Dot product.
     */
    double dot(Point p) {
        return x*p.x + y*p.y;
    }

    
    /**
     * Cross product.
     */
    double cross(Point p) {
        return x*p.y - y*p.x;
    }

    
    /**
     * Distance from origo.
     */
    double length() {
        return std::sqrt(x*x + y*y);
    }
};


/**
 * 2D line segment.
 */
struct LineSegment {
    Point first, second;

    
    /**
     * Length.
     */
    double length() {
        return (second - first).length();
    }

    
    /**
     * Calculate the shortest distance to the given point.
     * http://paulbourke.net/geometry/pointlineplane/
     */
    double distance(Point& p) {
        double len = length();
        if (len == 0)
            return (first - p).length();

        Point d = second - first;

        double u = ((p.x - first.x)*d.x + (p.y - first.y)*d.y) / (len*len);

        if (u < 0) // Closest to start of line.
            return (p - first).length();
        else if (u > 1) // Closest to end of line.
            return (p - second).length();
        else // Closest point is somewhere else on the line.
            return (p - (first + d*u)).length();
    }

    
    /**
     * Calculate the shortest distance to the given line segment.
     */
    double distance(LineSegment& other) {
        if (intersects(other)) return 0;

        return std::min({ distance(other.first),
                          distance(other.second),
                          other.distance(first),
                          other.distance(second)});
    }

    
    /**
     * Does this line segment intersect with the given
     * line segment?
     * http://www.cs.swan.ac.uk/~cssimon/line_intersection.html
     */
    bool intersects(LineSegment& other) {
        Point d1 = second - first;
        Point d2 = other.second - other.first;

        double d = d2.cross(d1);
        if (d == 0) return false;

        Point d3 = first - other.first;
        double a = d3.cross(d2) / d;
        double b = d3.cross(d1) / d;

        return 0 <= a && a <= 1 && 0 <= b && b <= 1;
    }
};


/**
 * Read line segment from stdin.
 */
LineSegment read_segment() {
    Point first, second;
    std::cin >> first.x >> first.y
             >> second.x >> second.y;
    return { first, second };
}


/**
 * Main.
 */
int main() {
    int test_count;
    std::cin >> test_count;
    while (test_count--) {
        LineSegment a = read_segment();
        LineSegment b = read_segment();
        std::cout << std::fixed << std::setprecision(2)
                  << a.distance(b)
                  << std::endl;
    }
}
