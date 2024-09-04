#ifndef BASICS_OF_PROGRAMMING_11LABA_H
#define BASICS_OF_PROGRAMMING_11LABA_H

struct Triangle {
    double x1, y1;  // Координаты первой вершины
    double x2, y2;  // Координаты второй вершины
    double x3, y3;  // Координаты третьей вершины
};

double Distance(double x1, double y1, double x2, double y2);

double TrianglePerimeter(struct Triangle triangle);

double TriangleArea(struct Triangle triangle);

#endif //BASICS_OF_PROGRAMMING_11LABA_H
