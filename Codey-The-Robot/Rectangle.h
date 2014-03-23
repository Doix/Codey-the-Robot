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

	bool contains(int px, int py) const
	{
		if (px < x) return false;
		if (py < y) return false;
		if (px >= x + width) return false;
		if (py >= y + height) return false;
		return true;
	}

	// needed so that we can use Rectangle as a key for std::map
	bool operator<(const Rectangle& rect1) const {
		return (x + y + width + height) < (rect1.x + rect1.y + rect1.width + rect1.height);
	}

private:
	const int x, y, width, height; 
};

#endif //RECTANGLE_H_