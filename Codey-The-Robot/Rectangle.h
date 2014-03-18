#ifndef RECTANGLE_H_
#define RECTANGLE_H_

class Rectangle
{
public:
	Rectangle(int x, int y, int width, int height) :
		x(x), y(y), 
		width(width), height(height){}
	int getLeft() const  { return x; }
	int getRight() const { return x + width; }
	int getTop() const { return y; }
	int getBottom() const { return y + height; }

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	bool collidesWith(const Rectangle& other) const{
		return getRight() >= other.getLeft() &&
			getLeft() <= other.getRight() &&
			getTop() <= other.getBottom() &&
			getBottom() >= other.getTop();
	}
private:
	const int x, y, width, height; 
};

#endif //RECTANGLE_H_