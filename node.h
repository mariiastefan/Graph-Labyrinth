#ifndef NODE_H
#define NODE_H


#include <QPainter>

class Node
{
    QPoint point;
    int number;
    std::string color;

public:
    Node(){ number = -1; };
    Node(QPoint p){
        point = p;
    }
    QPoint getPoint() {
        return point;
    }
    int getNumber() {
        return number;
    }
    void setNumber(int number) {
        this->number = number;
    }
     void setColor(std::string col)
     {
         color=col;
     }
     std::string getColor()
     {
         return color;
     }

};


#endif // NODE_H
