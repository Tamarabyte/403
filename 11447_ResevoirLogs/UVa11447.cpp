/* UVa problem: 11447 - ResevoirLogs
 *
 * Topic: Geometry
 *
 * Level: trivial
 *
 * Brief problem description:
 *
 * Solution Summary:
 *
 * Used Resources:
 *   Competitive Programming 3 by Steven Halim and Felix Halam
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

using namespace std;

double EPS = numeric_limits<double>::epsilon();

// Point data structure
struct Point {
  double x, y;
  Point() : x(0), y(0) {}
  Point(double x, double y) : x(x), y(y) {}
  void print() { printf("(%lf, %lf)\n", x, y); }
};

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


int main() {
    int tests, n, width;
    double percent, spent, gained, volume, current; 
    vector<Point> points;
    
    scanf("%d", &tests);
    while(tests--) {
        scanf("%d", &n);
        points.clear();
        
        while(n--) {
            Point point;
            scanf("%lf %lf", &point.x, &point.y);
            points.push_back(point);
        }
        
        scanf("%d", &width);
        scanf("%lf %lf %lf", &percent, &spent, &gained);
        
        //printf("initial: %lf%%, width: %d, spent: %lf, gained: %lf \n", percent, width, spent, gained);
        //printf("area: %lf\n", area(points));
        volume = width * area(points);
        //printf("volume: %lf\n", volume);
        current = volume * (percent/100);
        
        //printf("current: %lf\n", current);
        
        if ((current - spent) < 0) {
            printf("Lack of water. ");
            current = 0;
        }
        else {
            current -= spent;
        }
        
        //printf("\nafter spent: %lf\n", current);
        
        if((current + gained - volume) >= EPS) {
            printf("Excess of water. ");
            current = volume;
        }
        else {
            current += gained;
        }
        
        //printf("\nafter add: %lf\n", current);
        
        printf("Final percentage: %d%%\n", (int)((current/volume)*100));
        
        //printf("-----------\n");
    }

}