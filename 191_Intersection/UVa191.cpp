/* UVa problem: 191 - Intersection
 *
 * Topic: Geometry
 *
 * Level: non-trivial
 *
 * Brief problem description:
 *  Given a two points represnting a line segment and two points representing
 *  cross corners of a rectangle print "T" or "F" for whether
 *  or not the line segment intersects the rectangle.
 *
 * Solution Summary:
 *  I used a point and segment data structure and implemented methods
 *  for comparison between point segments. At first I thought it would
 *  be sufficient to check for intersection between segments (check if
 *  lines intersect, check if intersection point is within the bounding box
 *  of both segments). After getting WA and combing through the question
 *  it actually states intersection to be ANY area of the rectangle.
 *  So I had to add another check for when the line is inside the rectangle
 *  (not intersecting it's lines).
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   https://www.topcoder.com/community/data-science/data-science-tutorials/geometry-concepts-line-intersection-and-its-applications/
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
#include <algorithm>

using namespace std;

double EPS = numeric_limits<double>::epsilon();

// Point data structure
struct Point {
  double x, y;
  Point() : x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}
  void print() { printf("(%lf, %lf)\n", x, y); }
};

// ax + by + c = 0
// Line segment data structure
// Referenced code in competitive programming 3
struct Segment {
    double a, b, c;
    Point top, bot;

    Segment(Point p1, Point p2) : top(p1), bot(p2) {
         // default case for vertical lines
        if (fabs(p1.x - p2.x) < EPS) {
            a = 1.0;
            b = 0.0;
            c = -p1.x;
            return;
        }

        a = -(double)(p1.y - p2.y) /(p1.x - p2.x);
        b = 1.0;
        c = -(double)(a * p1.x) - p1.y;
    }

    // returns true if two lines are parallel
    bool isParallel(Segment &other) {
        return (fabs(a - other.a) <= EPS)
            && (fabs(b - other.b) <= EPS);
    }

    // checks whether or not the point is
    // in the bounding box
    bool inBoundingBox(Point &p) {

        return (min(top.x, bot.x) <= p.x && p.x <= max(top.x, bot.x)
        && min(top.y, bot.y) <= p.y  && p.y <= max(top.y, bot.y));
    }

    // returns true if two lines are equal
    bool isOverlap(Segment &other) {
        if (!(isParallel(other) && (fabs(c - other.c) < EPS)))
            return false;

        return (inBoundingBox(other.top) || inBoundingBox(other.bot));
    }

    // returns true if two lines intersect
    bool intersects(Segment &other) {
        if (isOverlap(other))
            return true;

        if (isParallel(other))
            return false;

        Point p;
        //printf("finding point of intersect\n");

        p.x = (other.b * c - b * other.c) / (other.a * b - a * other.b);

        if (fabs(other.b) <= EPS)
            p.y = -(a * p.x + c);
        else
            p.y = -(other.a * p.x + other.c);

        return (inBoundingBox(p) && other.inBoundingBox(p));
    }

    void print() {
        printf("LINE = a: %lf, b: %lf, c: %lf\n", a, b, c);
    }
};

int main() {
    int tests;
    Point p1, p2, topLeft, botRight;

    scanf("%d", &tests);

    while(tests--) {
        scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
              &p1.x, &p1.y, &p2.x, &p2.y, &topLeft.x, &topLeft.y, &botRight.x, &botRight.y);

        Segment seg(p1, p2);
        // left side
        Segment side1(topLeft, Point(topLeft.x, botRight.y));
        // right side
        Segment side2(botRight, Point(botRight.x, topLeft.y));
        // top
        Segment side3(topLeft, Point(botRight.x, topLeft.y));
        // bottom
        Segment side4(botRight, Point(topLeft.x, botRight.y));

        // extra case here for inside but not intersecting
        if (seg.intersects(side1) || seg.intersects(side2)
            || seg.intersects(side3) || seg.intersects(side4)
            || (min(topLeft.x, botRight.x) <= seg.top.x
                && max(topLeft.x, botRight.x) >= seg.top.x
                && min(topLeft.y, botRight.y) <= seg.top.y
                && max(topLeft.y, botRight.y)  >= seg.top.y))
            printf("T\n");
        else
            printf("F\n");
    }
}

