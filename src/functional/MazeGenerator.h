#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <random>

class MazeGenerator
{
public:
	static std::shared_ptr<std::vector<std::vector<char>>> generate(unsigned width, unsigned height)
	{
		// Проверим ограничения параметров на 0
		if ((width < 1) || (height < 1))
			return nullptr;

		const auto top_limit = std::numeric_limits<unsigned>::max();
		// Проверим ограничения по максимальному допустимому размеру
		if (((top_limit - 1) / 2 <= width) || ((top_limit - 1) / 2 <= height))
			return nullptr;

		// Инициализируем размер конечной матрицы maze
		// Ячейки будут представлять из себя фрагменты 2x2 + 1 одно значение сверху и слева для стен
		const unsigned output_height = height * 2 + 1;
		const unsigned output_width = width * 2 + 1;
		// Инициализируем указатель на лабиринт
		auto maze = std::make_shared<std::vector<std::vector<char>>>();
		// Зарезервируем размер лабиринта по высоте
		maze.get()->reserve(output_height);

		// Инициализируем построчно пустой лабиринт со стенами по периметру и "опорами" (стенами) в нижнем правом углу ячеек 2x2
		// #######
		// #     #
		// # # # #
		// #     #
		// #######
		for (unsigned i = 0; i < output_height; ++i)
		{
			std::vector<char> row;
			row.reserve(output_width);
			for (unsigned j = 0; j < output_width; ++j)
				// Если этот элемент в строке является ячейкой в левом верхнем угле области 2x2 - то это пустая ячейка в лабиринте
				if ((i % 2 == 1) && (j % 2 == 1))
					row.push_back(' ');
				else
					// Если это область для стены справа или область для стены снизу - то инициализируем этот элемент пустой ячейкой в лабиринте
					if (((i % 2 == 1) && (j % 2 == 0) && (j != 0) && (j != output_width - 1)) ||
						((j % 2 == 1) && (i % 2 == 0) && (i != 0) && (i != output_height - 1)))
						row.push_back(' ');
					else 
						// Во всех остальных случаях устанавливаем стену
						row.push_back('#');
			maze.get()->push_back(std::move(row));
		}
		
		//1. Создайте первую строку лабиринта.Ниодна ячейка не будет принадлежать какому - либо множеству.
		// Инициализируем вспомогательную строку, которая будет содержать в себе принадлежность ко множеству для ячейки из алгоритма
		std::vector<unsigned> row_set;
		row_set.reserve(width);
		// 0 - будет означать, что ячейка не принадлежит никакому множеству
		for (unsigned i = 0; i < width; ++i)
			row_set.push_back(0);
		// И инициализируем счетчик для множеств
		unsigned set = 1;
		// Инициализируем генератор случайных чисел
		std::random_device rd;
		std::mt19937 mt(rd());
		// от 0 до 2 (2 не входит) и после привидения к int будет либо 0 - где стены нет, либо 1 - стену решили установить
		std::uniform_int_distribution<int> dist(0, 2);
		// Организуем цикл алгоритма Эллера
		for (unsigned i = 0; i < height; ++i)
		{			
			//2. Присвоить каждой ячейке, которая не входит ни в одно множество, своё уникальное множество.
			for (unsigned j = 0; j < width; ++j)
				if (row_set[j] == 0)
					row_set[j] = set++;

			//3. Создайте правые стены для ячеек, двигаясь слева направо, следующим образом :
			for (unsigned j = 0; j < width - 1; ++j)
			{
				//	* Случайным образом решите, добавлять стену или нет
				const auto right_wall = dist(mt);
				//		* Если текущая ячейка и ячейка справа являются членами одного и того же множества, всегда создавайте между ними стену(это предотвратит петли)
				if ((right_wall == 1) || (row_set[j] == row_set[j + 1]))
					maze.get()->at(i * 2 + 1/*верхний ряд в i-ом ряду ячеек 2x2*/).at(j * 2 + 2/*Правый столбец в (i;j) ячейке 2x2*/) = '#';/*Создаем стену*/				
				else
				{
					//		* Если вы решите не добавлять стену, то объедините множества, к которым относятся текщая ячейка и ячейка справа
					const auto changing_set = row_set[j + 1];
					for (unsigned l = 0; l < width; ++l)
						if (row_set[l] == changing_set)
							row_set[l] = row_set[j];
				}
			}

			//4. Создайте нижние стены, двигаясь слева направо :
			for (unsigned j = 0; j < width; ++j)
			{				
				//	* Случайным образом решите, добавлять нижнюю стену или нет. 
				const auto bottom_wall = dist(mt);
				//		* Если ячейка является единственным членом своего множества, то не создавайте нижнюю стену
				unsigned int count_current_set = 0;
				for (unsigned l = 0; l < width; ++l)
					// считаем количество ячеек текущего множества
					if (row_set[j] == row_set[l])
						count_current_set++;
				//		* Если ячейка является единственным членом своего множества, которая не имеет нижней стены, то не создавайте нижнюю стену
				if ((bottom_wall == 1) && (count_current_set != 1))
					maze.get()->at(i * 2 + 2).at(j * 2 + 1) = '#';
			}
						
			//5. Решите, продолжать добавлять строки или остановиться и завершить лабиринт
			//	* Если вы решите добавить еще одну строку :
			if (i != height - 1)
			{
				//*Важно : *Убедитесь, что каждая область имеет по крайней мере одну ячейку без нижней стены(это предотвратит создание изолированных областей)
				for (unsigned j = 0; j < width; ++j) {
					unsigned count_hole = 0;
					for (unsigned l = 0; l < width; ++l)
						if ((row_set[l] == row_set[j]) && (maze.get()->at(i * 2 + 2).at(l * 2 + 1) == ' '))
							count_hole++;
					if (count_hole == 0)
						maze.get()->at(i * 2 + 2).at(j * 2 + 1) = ' ';
				}

				//		* скопируйте текущую строку
				//		* удалите в новой строку все правые стены
				/// Правые стенки в инициализированном массиве у нас уже отсутствуют в каждой новой строке
				//		* удалите ячейки с нижней стеной из их множества
				for (unsigned j = 0; j < width; ++j)
					if (maze.get()->at(i * 2 + 2/* Проверим надичие нижней стены у текущего ряда*/).at(j * 2 + 1) == '#')
						// Если стенка есть, то удаляем ячейку из множества
						row_set[j] = 0;
				//		* удалите все нижние стены
				/// Нижние стены в каждом новом ряду ячеек отсутствуют (заложено при инициализации)
			}
			//		* продолжить с шага 2.
		}

		//	* Если вы решили закончить лабиринт :
		//		*добавьте нижнюю стену каждой ячейке
		/// Нижняя стена построена при инициализации лабиринта
		//		* перемещайтесь слева направо :
		for (unsigned int j = 0; j < width - 1; ++j)
		{
			//			*Если текущая ячейка и ячейка справа являются членами разных множеств, то :
			if (row_set[j] != row_set[j + 1])
			{
				//			*удалить правую стену
				maze.get()->at(output_height - 2).at(j * 2 + 2) = ' ';
				//			* объедините множества, к которым принадлежат текущая ячейка и ячейка справа
				unsigned int changing_set = row_set[j + 1];
				for (unsigned int l = j + 1; l < width - 1; ++l)
					if (row_set[l] == changing_set)
						row_set[l] = row_set[j];
			}
			//			* вывод итоговой строки
		}
		// вернем указатель на полученный лабиринт
		return maze;
	}

	static void print(const std::shared_ptr<std::vector<std::vector<char>>>& maze)
	{
		// Проверяем указатель на nullptr
		if (maze == nullptr)
			return;

		// Построчно считываем и выводим в консоль
		for (unsigned i = 0; i < maze.get()->size(); ++i)
		{
			for (unsigned j = 0; j < maze.get()->at(0).size(); ++j)
				std::cout << maze.get()->at(i).at(j);
			std::cout << std::endl;
		}
	}

	//static void save_to_file(const std::shared_ptr<std::vector<std::vector<char>>>& maze)
	//{
	//	
	//}

private:
	MazeGenerator() = default;
};
