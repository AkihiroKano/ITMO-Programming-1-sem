#include <stdio.h>
#include "Lab 11 Triangle.h"

int main() {

    struct Triangle triangle;

    printf("x1 y1\n");
    scanf("%lf %lf", &triangle.x1, &triangle.y1);
    printf("x2 y2\n");
    scanf("%lf %lf", &triangle.x2, &triangle.y2);
    printf("x3 y3\n");
    scanf("%lf %lf", &triangle.x3, &triangle.y3);

    double perimeter = TrianglePerimeter(triangle);
    printf("Perimeter: %lf\n", perimeter);

    double area = TriangleArea(triangle);
    printf("Area: %lf\n", area);

}