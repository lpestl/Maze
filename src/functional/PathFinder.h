// PathFinder.h
#pragma once

#include "Position2D.h"
#include "Direction2D.h"
#include <vector>
#include <map>
#include <memory>

class PathFinder
{
public:
	PathFinder();
	~PathFinder();
	// Метод для инициализации игрока
	void init(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze);	
	// Метод для следующего шага игрока
	virtual void nextStep();

	// Метод для получения количества посещенных ячеек лабиринта
	unsigned getCountVisitedCells() { return map_.size() + 1; }
	// Метод для получения длинны кратчайшего пути (в процессе поиска пути - он может быть не достоверный)
	unsigned getShortWayLenght() { return short_way_.size() + 1; }
	// Метод, чтобы спросить, добрался ли игрок до точки выхода
	bool isWin() { return is_win_; }

protected:
	bool is_win_;	// Флаг, который отображает, добрался ли игрок до точки выхода

	Position2D current_position_;							// Текущая позиция игрока
	Direction2D current_direction_;							// Текущее направление игрока

	std::map<Position2D, bool> map_;						// Все посещённые ячейки. Абстрактная "карта"
	std::vector<Position2D> short_way_;						// Вектор, который будет хранить координаты только кратчайшего пути
	
	std::shared_ptr<std::vector<std::vector<char>>> maze_;	// Указатель на лабиринт, по которому мы будем передвигаться
};
