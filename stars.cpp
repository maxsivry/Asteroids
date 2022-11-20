//
// Created by Max Ivry on 11/20/22.
//

#include "stars.h"
#include "graphics.h"

Stars::Stars() : Shape(), radius(0) {
}

Stars::Stars(double radius) : Shape() {
    setRadius(radius);
}

Stars::Stars(color fill) : Shape(fill), radius(0) {
}

Stars::Stars(point2D center) : Shape(center), radius(0) {
}

Stars::Stars(color fill, point2D center) : Shape(fill, center), radius(0) {
}

Stars::Stars(double red, double green, double blue, double alpha) : Shape(red, green, blue, alpha), radius(0) {
}

Stars::Stars(double x, double y) : Shape(x, y), radius(0) {
}

Stars::Stars(double red, double green, double blue, double alpha, double x, double y) : Shape(red, green, blue, alpha, x, y), radius(0) {
}

Stars::Stars(color fill, double x, double y) : Shape(fill, x, y), radius(0) {
}

Stars::Stars(double red, double green, double blue, double alpha, point2D center) : Shape(red, green, blue, alpha, center), radius(0) {
}

Stars::Stars(color fill, double radius) : Shape(fill) {
    setRadius(radius);
}

Stars::Stars(point2D center, double radius) : Shape(center) {
    setRadius(radius);
}

Stars::Stars(color fill, point2D center, double radius) : Shape(fill, center) {
    setRadius(radius);
}

Stars::Stars(double red, double green, double blue, double alpha, double radius) : Shape(red, green, blue, alpha) {
    setRadius(radius);
}

Stars::Stars(double x, double y, double radius) : Shape(x, y) {
    setRadius(radius);
}

Stars::Stars(double red, double green, double blue, double alpha, double x, double y, double radius) : Shape(red, green, blue, alpha, x, y) {
    setRadius(radius);
}

Stars::Stars(color fill, double x, double y, double radius) : Shape(fill, x, y) {
    setRadius(radius);
}

Stars::Stars(double red, double green, double blue, double alpha, point2D center, double radius) : Shape(red, green, blue, alpha, center) {
    setRadius(radius);
}

double Stars::getRadius() const {
    return radius;
}

double Stars::getLeftX() const {
    return center.x - radius;
}

double Stars::getRightX() const  {
    return center.x + radius;
}

double Stars::getTopY() const {
    return center.y - radius;
}

double Stars::getBottomY() const {
    return center.y + radius;
}

void Stars::setRadius(double r) {
    if (r < 0) {
        r = 0;
    }
    radius = r;
}

void Stars::changeRadius(double delta) {
    setRadius(radius + delta);
}

void Stars::draw() const {
    // Set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // Draw Stars as Triangle Fan
    glBegin(GL_TRIANGLE_FAN);
    // Draw center point
    glVertex2i(center.x, center.y);
    // Draw points on edge of Stars
    for (double i = 0; i < 2.0*PI+0.05; i += (2.0*PI)/360.0) {
        glVertex2i(center.x + (radius * cos(i)),
                   center.y + (radius * sin(i)));
    }
    // End Triangle Fan
    glEnd();
}