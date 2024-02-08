// square.h
#ifndef SQUARE_H
#define SQUARE_H

class Square {
private:
    int x; // x-coordinate of the square's center
    int y; // y-coordinate of the square's center
    int size; // size of the square

public:
    // Constructor
    Square(int centerX, int centerY, int size);

    // Destructor
    ~Square();

    // Setter functions
    void setCenterX(int centerX);
    void setCenterY(int centerY);
    void setSize(int size);

    // Getter functions
    int getCenterX() ;
    int getCenterY() ;
    int getSize() ;

    // Other member functions
    void draw() const; // Display information about the square
};

#endif
