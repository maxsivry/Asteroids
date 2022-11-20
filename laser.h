
#include "rect.h"
#include "circle.h"
class laser : public Rect {
private:

public:
    int xDirection;
    int yDirection;
    laser(int xDirection, int yDirection, point2D center);
    //bool isOverlapping(Circle c);
    int getXdir();
    int getYdir();
};
