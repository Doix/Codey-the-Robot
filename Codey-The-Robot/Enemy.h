#ifndef ENEMY_H_
#define ENEMY_H_

#include <memory>

namespace{

}

class Graphics;
class Sprite;

class Enemy
{
public:
	Enemy(Graphics& graphics, int PosX, int PosY);
	~Enemy();

	void draw(Graphics& graphics) const;
	void update(const int elapsed_time_ms);
private:
	int PosX;
	int PosY;

	std::shared_ptr<Sprite> sprite;


};

#endif // ENEMY_H_