/* UVa problem: 378 - IntersectingLines
 *
 * Topic: Geometry
 *
 * Level: trivial
 *
 * Brief problem description:
 *  Given a list of 8 coordinates (x1 y1 ... x4 y4)
 *  construct two lines out of these coordinates and
 *  output whether these are parallel, intersect across
 *  a line (are the same), or their point of intersection.
 *
 * Solution Summary:
 *  Implemented a Point and Line class and methods to determine
 *  parallelization, equality and point of intersection
 *  for my line class.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   http://www.cplusplus.com/reference/limits/numeric_limits/
 *
 * I hereby certify that I have produced the following solution myself
 * using the resources listed above in accordance with the CMPUT 403
 * collaboration policy.
 *
 * --- Tamara Bain
 *
 * Language: C++11
 */

#include <cstdio>
#include <cmath>
#include <limits>

using namespace std;

double EPS = numeric_limits<double>::epsilon();

// Point data structure
struct Point {
  double x, y;
  Point() : x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}
};

// ax + by + c = 0
// Line data structure
// Code for line operations referenced from Competitive Programming 3
struct Line {
    double a, b, c;

    Line() : a(0), b(0), c(0) {}

    // returns true if two lines are parralel
    // within the accuracy of a double
    bool isParallel(Line &other) {
        return (fabs(a - other.a) <= EPS)
            && (fabs(b - other.b) <= EPS);
    }

    // returns true if two lines are equal
    bool operator==(Line &other) {
        return (isParallel(other) && (fabs(c - other.c) < EPS));
    }

    // returns true if two lines intersect
    // sets the point x and y to the point of
    // intersection if they do
    bool intersects(Line &other, Point &p) {
        if (isParallel(other))
            return false;

        p.x = (other.b * c - b * other.c) / (other.a * b - a * other.b);

        if (fabs(other.b) <= EPS)
            p.y = -(a * p.x + c);
        else
            p.y = -(other.a * p.x + other.c);

        return true;
    }

    void print() {
        printf("LINE = a: %lf, b: %lf, c: %lf\n", a, b, c);
    }
};

// given two points converts a point to a line
// code referenced from Competitive Programming 3
Line pointsToLine(Point p1, Point p2) {
    Line line;

    // default case for vertical lines
    if (fabs(p1.x - p2.x) < EPS) {
        line.a = 1.0;
        line.b = 0.0;
        line.c = -p1.x;
        return line;
    }

    line.a = -(double)(p1.y - p2.y) /(p1.x - p2.x);
    line.b = 1.0;
    line.c = -(double)(line.a * p1.x) - p1.y;

    return line;
}

int main() {
    int pairs;
    Point p1, p2, p3, p4, pIntersect;
    Line lineA, lineB;

    printf("INTERSECTING LINES OUTPUT\n");

    scanf("%d", &pairs);
    while(pairs--) {

        scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
              &p1.x, &p1.y, &p2.x, &p2.y, &p3.x, &p3.y, &p4.x, &p4.y);

        // make lines and print results of comparison
        lineA = pointsToLine(p1, p2);
        lineB = pointsToLine(p3, p4);

        if (lineA == lineB)
            printf("LINE\n");
        else if (lineA.isParallel(lineB))
            printf("NONE\n");
        else if (lineA.intersects(lineB, pIntersect))
            printf("POINT %.2lf %.2lf\n", pIntersect.x, pIntersect.y);
    }
    printf("END OF OUTPUT\n");
}
