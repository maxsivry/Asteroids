//
// Created by Max Ivry on 11/20/22.
//

#ifndef MARIEGER_MIVRY_STARS_H
#define MARIEGER_MIVRY_STARS_H


#include "shape.h"

class Stars : public Shape {
private:
    double radius;
public:
    /* Constructors */
    Stars();
    explicit Stars(double radius);
    explicit Stars(color fill);
    explicit Stars(point2D center);
    Stars(color fill, point2D center);
    Stars(double red, double green, double blue, double alpha);
    Stars(double x, double y);
    Stars(double red, double green, double blue, double alpha, double x, double y);
    Stars(color fill, double x, double y);
    Stars(double red, double green, double blue, double alpha, point2D center);
    Stars(color fill, double radius);
    Stars(point2D center, double radius);
    Stars(color fill, point2D center, double radius);
    Stars(double red, double green, double blue, double alpha, double radius);
    Stars(double x, double y, double radius);
    Stars(double red, double green, double blue, double alpha, double x, double y, double radius);
    Stars(color fill, double x, double y, double radius);
    Stars(double red, double green, double blue, double alpha, point2D center, double radius);

    /* Destructor */
    virtual ~Stars() = default;

    /* Getters */
    double getRadius() const;
    double getLeftX() const override;
    double getRightX() const override;
    double getTopY() const override;
    double getBottomY() const override;

    /* Setter */
    void setRadius(double r);
    void changeRadius(double delta);

    /* Draw */
    void draw() const override;

};


#endif //MARIEGER_MIVRY_STARS_H
