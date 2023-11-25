#ifndef OBSTACLE_H
#define OBSTACLE_H

//TODO: id, location, diameter

class Obstacle
{
public:
    Obstacle();
    void setXCoordinate(int newXCoordinate);

    int yCoordinate() const;
    void setYCoordinate(int newYCoordinate);

    int xCoordinate() const;

private:
    int m_id;
    int m_xCoordinate;
    int m_yCoordinate;
};

#endif // OBSTACLE_H
