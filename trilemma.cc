// William Sjöblom
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iostream>


/**
 * Vertex.
 */
struct Vertex {
    long x, y;
};


/**
 * Triangle.
 */
struct Triangle {
    Vertex vertices[3];
    Vertex& operator[](int i) { return vertices[i]; }
};


/**
 * Is this a triangle (i.e. are the vertices non collinear)?
 */
bool is_triangle(Triangle& tri) {
    http://mathworld.wolfram.com/Collinear.html
    return 0 != (tri[0].x * (tri[1].y - tri[2].y) +
                 tri[1].x * (tri[2].y - tri[0].y) +
                 tri[2].x * (tri[0].y - tri[1].y));
}


/**
 * Euclidian distance squared.
 */
long distance2(Vertex& v0, Vertex& v1) {
    long dx = v0.x - v1.x;
    long dy = v0.y - v1.y;
    return std::abs(dx*dx + dy*dy);
}


/**
 * Analyze triangle.
 */
void analyze(Triangle& tri) {
    if (!is_triangle(tri)) {
        std::cout << "not a triangle" << std::endl;
        return;
    }
    
    float side2[3];
    side2[0] = distance2(tri[0], tri[1]);
    side2[1] = distance2(tri[1], tri[2]);
    side2[2] = distance2(tri[2], tri[0]);
    std::sort(std::begin(side2), std::end(side2));
    
    if (side2[0] == side2[1] || side2[1] == side2[2])
        std::cout << "isosceles ";
    else
        std::cout << "scalene ";

    if (side2[0] + side2[1] == side2[2])
        std::cout << "right triangle";
    else if (side2[0] + side2[1] < side2[2])
        std::cout << "obtuse triangle";
    else
        std::cout << "acute triangle";

    std::cout << std::endl;
}


int main() {
    int tri_count; scanf("%d", &tri_count);

    for (int i = 0; i < tri_count; i++) {
        Triangle tri;
        scanf("%ld %ld %ld %ld %ld %ld",
              &tri.vertices[0].x, &tri.vertices[0].y,
              &tri.vertices[1].x, &tri.vertices[1].y,
              &tri.vertices[2].x, &tri.vertices[2].y);

        std::cout << "Case #" << i + 1 << ": ";
        analyze(tri);
    }
}
