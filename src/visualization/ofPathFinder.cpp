#include "ofPathFinder.h"
#include "ofxTweener.h"

void ofPathFinder::setup(Position2D start_position, std::shared_ptr<std::vector<std::vector<char>>> maze)
{
	// При первоначальной инициализации удалим все ранее запущенные анимации
	Tweener.removeAllTweens();
	is_animated_ = false;
	is_runed_ = false;
	// Запустим инициализацию базового класса
	init(start_position, maze);
	// Инициализируем начальные экранные координаты
	screen_x_ = current_position_.X;
	screen_y_ = current_position_.Y;
}

void ofPathFinder::update()
{
	// Если не запущен - то ничего не делаем
	if (!is_runed_) return;
	// Если запущен и уже добрался до конца - ничего не делаем
	if (is_win_) return;
	// Если еще не добрался до выхода, запущен и анимирован, то делаем следующий шаг
	if (!is_animated_)
		nextStep();
}

void ofPathFinder::draw()
{
	// Проверяем лабиринт
	if (maze_ == nullptr) return;	
	// Сначала серым закрасим все посещенные ранее ячейки
	ofSetHexColor(0x33555555);
	for (auto& pos : map_)
		ofDrawRectangle(pos.first.X, pos.first.Y, 1, 1);
	// Теперь зеленым отметим кратчайший путь
	ofSetHexColor(0x5500FF00);
	for (auto& pos : short_way_)
		ofDrawRectangle(pos.X, pos.Y, 1, 1);
	// И красным нарисуем самого "игрока"
	ofSetHexColor(0x77FF0000);
	ofDrawRectangle(screen_x_, screen_y_, 1, 1);
}

void ofPathFinder::run()
{
	// Запускаем игрока
	is_runed_ = true;
}

void ofPathFinder::nextStep()
{
	// Запоминаем текущие координты игрока
	screen_x_ = current_position_.X;
	screen_y_ = current_position_.Y;
	// Создаем callback, который будет вызываться при окончании анимации
	auto callback = std::bind(&ofPathFinder::endAnimation, this, std::placeholders::_1);
	// Вызывем базовый метод для выполнения следующего шага
	PathFinder::nextStep();
	// И анимируем перемещение игрока
	if (is_win_)
	{
		Tweener.addTween(screen_x_, static_cast<float>(current_position_.X), /* Длительность анимации */0.1F, &ofxTransitions::linear);
		Tweener.addTween(screen_y_, static_cast<float>(current_position_.Y), /* Длительность анимации */0.1F, &ofxTransitions::linear);
	} else
	{
		Tweener.addTween(screen_x_, static_cast<float>(current_position_.X), /* Длительность анимации */0.1F, &ofxTransitions::linear, callback);
		Tweener.addTween(screen_y_, static_cast<float>(current_position_.Y), /* Длительность анимации */0.1F, &ofxTransitions::linear, callback);
	}
}
