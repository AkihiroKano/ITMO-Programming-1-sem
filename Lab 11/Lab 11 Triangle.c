#include "Lab 11 Triangle.h"
#include <math.h>

double Distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double TrianglePerimeter(struct Triangle triangle) {
    double side_length_1 = Distance(triangle.x1, triangle.y1, triangle.x2, triangle.y2);
    double side_length_2 = Distance(triangle.x2, triangle.y2, triangle.x3, triangle.y3);
    double side_length_3 = Distance(triangle.x3, triangle.y3, triangle.x1, triangle.y1);
    return side_length_1 + side_length_2 + side_length_3;
}

double TriangleArea(struct Triangle triangle) {
    double side_length_1 = Distance(triangle.x1, triangle.y1, triangle.x2, triangle.y2);
    double side_length_2 = Distance(triangle.x2, triangle.y2, triangle.x3, triangle.y3);
    double side_length_3 = Distance(triangle.x3, triangle.y3, triangle.x1, triangle.y1);
    double p = (side_length_1 + side_length_2 + side_length_3) / 2;
    return (sqrt(p * (p - side_length_1) * (p - side_length_2) * (p - side_length_3))) / side_length_1;
}
