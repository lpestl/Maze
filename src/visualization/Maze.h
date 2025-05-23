// Maze.h
#pragma once

#include <vector>
#include <memory>
#include "ofPathFinder.h"

class Maze
{
public:
	// метод для инициализации начальных занчений (аналог конструктора)
	void setup(int width, int height);
	// вызов метода происходит перед прорисовкой каждого кадра (предназначен для расчетов)
	void update();
	// метод для прорисовки кадра и отображения
	void draw();

	// метод, в котором мы будем просчитывать координаты и scale для лабиринта,
	// чтобы на следующем кадре он был отображен корректно по центру экрана
	void show_in_center();
	// Метод для запуска игрока
	void run() { player_.run(); }
	// Обработчики для событий самого приложения
	void windowResized(int w, int h);
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseScrolled(int x, int y, float scrollX, float scrollY);

private:
	// Указатель на сгенерированный лабиринт
	std::shared_ptr<std::vector<std::vector<char>>> maze_;
	// Коэффициент увеличения для корректного отображения на экране
	float scale_ = 0;
	// Смещение всего лабиринта относительно левого верхнего угла экрана
	int pos_x_ = 0;
	int pos_y_ = 0;
	// Последние значения позиции мыши 
	// (понадобяться для того, чтобы в дальнейшем мы могли "двигать" мышкой лабиринт)
	int last_mouse_pos_x_ = 0;
	int last_mouse_pos_y_ = 0;
	// Игрок
	ofPathFinder player_;
};

