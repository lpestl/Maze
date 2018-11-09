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

	void endAnimation(float *arg) { is_animated_ = false; }	// Callback функци€, котора€ будет срабатывать, когда анимаци€ заканчиваетс€

	void nextStep() override;
private:
	bool is_animated_;	// ‘лаг дл€ отслеживани€ состо€ни€, находитьс€ ли объект в процессе анимации (перемещени€ между €чейками)
	bool is_runed_;		// ‘лаг дл€ отображени€, запущен игрок или нет (в процессе ли он поиска)
	float screen_x_;	// Ёкранна€ координата X
	float screen_y_;	// Ёкранна€ координата Y
};

