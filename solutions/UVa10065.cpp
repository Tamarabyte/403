/* UVa problem: 10065 - UselessTilePackers
 *
 * Topic: Geometry
 *
 * Level: trivial
 *
 * Brief problem description:
 *      You are given a set of points representing a tile.
 *      Calculate the convex hull of the points and the
 *      area of the tile. Output the % of area between the
 *      convex hull and the tile.
 *
 * Solution Summary:
 *      Implemented the Graham Scan algorithm from competitive programming 3
 *      to calculate the convex hull. Used the determinate to get area.
 *      completed the set of points to form a polygon if neccesary.
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
 *   Hint of 'complete the polygon' from Mark Galloway
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
#include <vector>
#include <limits>

using namespace std;
double EPS = numeric_limits<double>::epsilon();

// Point data structure
struct Point {
    double x, y;
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}
  
    bool operator== (Point &other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); 
    }
    
    bool operator!= (Point &other) const {
        return !(operator==(other));
    }
};

// Vec data structure
struct vec { 
    double x, y; 
    vec(double _x, double _y) : x(_x), y(_y) {} 
};

// implentation referenced from Competitive Programming 3
double area(const vector<Point> points) {
    double result = 0.0, x1, y1, x2, y2;
    
    // calculate determinant
    for (int i = 0; i < (int)points.size()-1; i++) {
        x1 = points[i].x; 
        x2 = points[i+1].x;
        y1 = points[i].y; 
        y2 = points[i+1].y; 
        result += (x1 * y2 - x2 * y1);
    }
    
    // area is half of determininant 
    return fabs(result) / 2.0; 
}

Point pivot(0, 0);
vec toVec(Point a, Point b) { 
    return vec(b.x - a.x, b.y - a.y); 
}


double cross(vec a, vec b) { 
    return a.x * b.y - a.y * b.x; 
}

bool ccw(Point p, Point q, Point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; 
}

double dist(Point p1, Point p2) { 
    // Euclidean distance 
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy) 
    return hypot(p1.x - p2.x, p1.y - p2.y); 
}

bool collinear(Point p, Point q, Point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS;
}

bool angleCmp(Point a, Point b) {
    if (collinear(pivot, a, b))
        return dist(pivot, a) < dist(pivot, b);

    // angle-sorting function // special case // check which one is closer
    double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
    double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; 
}



// implentation from Competitive Programming 3
vector<Point> get_hull(vector<Point> P) { 
    int i, j, n = (int)P.size();
    
    // special case, the CH is P itself
    if (n <= 3) {
        if (!(P[0] == P[n-1])) 
            P.push_back(P[0]); 
        return P; 
    } 
    
    // first, find P0 = point with lowest Y and if tie: rightmost X int 
    int P0 = 0;
    for (i = 1; i < n; i++)
        if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x)) 
            P0 = i;
    
    Point temp = P[0]; 
    P[0] = P[P0]; 
        
    // swap P[P0] with P[0]
    P[P0] = temp; 
        
    //second, sort points by angle w.r.t. pivot P0
    // use this global variable as reference 
    pivot = P[0]; 
    // we do not sort P[0]
    sort(++P.begin(), P.end(), angleCmp); 

        
    vector<Point> S;
    S.push_back(P[n-1]); 
    S.push_back(P[0]); 
    S.push_back(P[1]); 
    i = 2; 
    
    // then, we check the rest 
    // note: N must be >= 3 for this method to work
    while (i < n) { 
        j = (int)S.size()-1;
        if (ccw(S[j-1], S[j], P[i])) 
            S.push_back(P[i++]); // left turn, accept 
        else S.pop_back(); // or pop the top of S until we have a left turn
    } 
    
    return S; 
}


int main() {
    int n, testcase = 0;
    double area_tile, area_container;
    vector<Point> points, hull;
    
    while(scanf("%d", &n), n) {
        ++testcase;
        points.clear();
        hull.clear();
        while(n--) {
            Point point;
            scanf("%lf %lf", &point.x, &point.y);
            points.push_back(point);
        }
        
        if(points.front() != points.back())
            points.push_back(points.front());
        
        area_tile = area(points);
        
        hull = get_hull(points);
        area_container = area(hull);
        printf("Tile #%d\n", testcase);
        printf("Wasted Space = %0.2lf %%\n\n", ((area_container - area_tile)/area_container)*100);
    }
}