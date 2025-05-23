// PathFinder.cpp
#include "PathFinder.h"

PathFinder::PathFinder() { }

PathFinder::~PathFinder() { }

void PathFinder::init(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze)
{
	// Очищаем историю перемещений 
	map_.clear();
	short_way_.clear();
	// Заполучаем лабиринт для проверки каждого шага
	maze_ = maze;
	// На старте мы еще не нашли точку выхода
	is_win_ = false;
	// 1. Зададим начальную позицию и направление игрока.
	// Стартовая позиция будет задана в крайней ячейке левого верхнего угла лабиринта
	current_position_ = start_position;
	// А начальное направление пусть будет "направо" (на восток)
	current_direction_ = RIGHT;	
}

void PathFinder::nextStep()
{
	// Если мы уже добрались до точки выхода, то не имеет смысла делать дополнительные шаги
	if (is_win_) return;

	// 2. Запоминаем координаты текущей ячейки, с учетом порядка посещения ячеек
	map_[current_position_] = true;
	short_way_.push_back(current_position_);

	// 3. Игрок поворачивается на 90 градусов **против часовой стрелки**
	current_direction_ = current_direction_ == UP ? LEFT : current_direction_ == LEFT ? DOWN : current_direction_ == DOWN ? RIGHT : UP;
	// Инициализируем временную переменную для проверки впереди стоящей ячейки
	Position2D forward_cell;
	do {
		// 4. Игрок проверяет ячейку, которая находиться перед ним :
		forward_cell = current_position_;
		switch (current_direction_) 
		{ 
			case RIGHT: forward_cell.X++; break;
			case DOWN: forward_cell.Y++; break;
			case LEFT: forward_cell.X--; break;
			case UP: forward_cell.Y--; break;
		}
		// 4.1. Если это стена :
			// * игрок поворачивается на 90 градусов **по часовой стрелке**
		current_direction_ = current_direction_ == UP ? RIGHT : current_direction_ == LEFT ? UP : current_direction_ == DOWN ? LEFT : DOWN;
			// * игрок повторяет _шаг 4_
	} while (maze_.get()->at(forward_cell.Y).at(forward_cell.X) == '#');

	// 4.2. Если это свободная ячейка :
		// * игрок выполняет _шаг 5_
	// Востановим правильное направление
	current_direction_ = current_direction_ == UP ? LEFT : current_direction_ == LEFT ? DOWN : current_direction_ == DOWN ? RIGHT : UP;
	
	// 5. Игрок переходит на новую свободную ячейку
	current_position_ = forward_cell;
	// 6. По истории всех посещенных ранее ячеек, проверяем был игрок в этой новой ячейке или нет :
	auto foundedIter = map_.find(forward_cell);
	// 6.1. Если игрок был в этой ячейке :
	if (foundedIter != map_.end())
	{
		// * удаляем из истории посещенных ячеек все записи, начиная с последней, до координат текущей ячейки 
		if (!short_way_.empty()) {
			while ((!short_way_.empty()) && ((short_way_.back().X != foundedIter->first.X) || (short_way_.back().Y != foundedIter->first.Y)))
			{
				short_way_.erase(--short_way_.end());
			}
			// **включительно**
			if (!short_way_.empty()) {
				short_way_.erase(--short_way_.end());
			}
		}
		// * переходим к _шагу 7_
	}
	// 6.2. Если игрок не был ранее в этой ячейке, то сразу переходим к _шагу 7_
	// 7. Проверяем, является ли текущая ячейка `точкой выхода`:
	// 7.1. Если она не является `точкой выхода`, то повторяем с _шага 2_
	// 7.2. Если это `точка выхода`, то _заканчиваем алгоритм_.	
	is_win_ = maze_.get()->at(current_position_.Y).at(current_position_.X) == 'X';
}
