// ofPathFinder.h
#pragma once

#include "PathFinder.h"

class ofPathFinder : public PathFinder
{
public:
	void setup(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze);
	void update();
	void draw();
	void run();

	void endAnimation(float *arg) { is_animated_ = false; }	// Callback функция, которая будет срабатывать, когда анимация заканчивается

	void nextStep() override;
private:
	bool is_animated_;	// Флаг для отслеживания состояния, находиться ли объект в процессе анимации (перемещения между ячейками)
	bool is_runed_;		// Флаг для отображения, запущен игрок или нет (в процессе ли он поиска)
	float screen_x_;	// Экранная координата X
	float screen_y_;	// Экранная координата Y
};

