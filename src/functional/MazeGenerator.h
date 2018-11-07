#pragma once
#include <vector>
#include <memory>

class MazeGenerator
{
public:
	static std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height)
	{
		// ѕроверим ограничени€ параметров на 0
		if ((width < 1) || (height < 1))
			return nullptr;

		auto top_limit = std::numeric_limits<unsigned>::max();
		// ѕроверим ограничени€ по максимальному допустимому размеру
		if (((top_limit - 1) / 2 <= width) || ((top_limit - 1) / 2 <= height))
			return nullptr;

		// »нициализируем размер конечной матрицы maze
		// ячейки будут представл€ть из себ€ фрагменты 2x2 + 1 одно значение сверху и слева дл€ стен
		unsigned output_height = height * 2 + 1;
		unsigned output_width = width * 2 + 1;
		// »нициализируем указатель на лабиринт и инициализируем его пустым значением
		auto maze = std::make_shared<std::vector<std::vector<char>>>(std::vector<std::vector<char>> {});
		// «арезервируем размер лабиринта по высоте
		maze.get()->reserve(output_height);

		// ...

		// вернем указатель на полученный лабиринт
		return maze;
	}

private:
	MazeGenerator() { }
};
