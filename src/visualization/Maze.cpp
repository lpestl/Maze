#include "Maze.h"
#include "MazeGenerator.h"
#include "ofMesh.h"
#include "ofBitmapFont.h"
#include "ofxTweener.h"

void Maze::setup(int width, int height)
{
	alpha_ = 0.0f;

	// Если ранее лабиринт был уже создан
	if (maze_ != nullptr)
		// то сбрасываем счетчик указателя
		maze_.reset();
	// Генерируем новый лабиринт
	maze_ = MazeGenerator::generate(width, height);

	// Добавим в лабиринт "точку выхода" в правый нижний угол учитывая наличие стен
	maze_.get()->at(maze_.get()->size() - 2).at(maze_.get()->at(0).size() - 2) = 'X';
	
	// Инициализация игрока
	player_.setup(Position2D{ 1, 1 }, maze_);

	// Нарисуем лабиринт в центре экрана
	show_in_center();
}

void Maze::update()
{
	// Обновление 
	player_.update();
}

void Maze::draw()
{
	// Проверяем, создан ли лабиринт
	if (maze_ == nullptr)
		return;
	// Запомним изначальную матрицу трансформирования сцены
	ofPushMatrix();
	// Сделаем сдвиг на подсчитаное смещение
	ofTranslate(pos_x_, pos_y_);
	// Увеличим размер конечного изображения на подсчитанный заранее масштаб
	ofScale(scale_, scale_);
	// Зададим общий фон ячеек прозрачным серо-голубым цветом
	//ofSetHexColor(0x777777FF);
	ofSetColor(128, 128, 255, alpha_ / 2);
	// Нарисуем фон в виде прямоугольника
	ofDrawRectangle(0, 0, maze_.get()->at(0).size(), maze_.get()->size());
	// Зададим черный цвет для стен
	//ofSetHexColor(0x000000);
	ofSetColor(0, 0, 0, alpha_);
	// И пробещим по массивы с лабиринтом
	for (size_t i = 0; i < maze_.get()->size(); ++i)
		for (size_t j = 0; j < maze_.get()->at(0).size(); j++)
			if (maze_.get()->at(i).at(j) == '#')
				// Отрисовывая при этом стены
				ofDrawRectangle(j, i, 1, 1);
	// Проверим точку выхода
	if (maze_.get()->at(maze_.get()->size() - 2).at(maze_.get()->at(0).size() - 2) == 'X')
	{
		// Зададим Зеленый цвет
		//ofSetHexColor(0xFF00FF00);
		ofSetColor(0, 255, 0, alpha_);
		// Нарисуем точку выхода
		ofDrawRectRounded(maze_.get()->at(0).size() - 2, maze_.get()->size() - 2, 1, 1, 0.3);
	}

	// Отрисовка игрока (причем она должна быть до того как мы вызовем ofPopMatrix)
	player_.draw();

	// Вернем матрицу трансформирования сцены в изначальное состояние
	ofPopMatrix();

	// А сообщение о конце пути, выводим после ofPopMatrix
	if (player_.isWin())
	{
		std::stringstream reportStr;
		reportStr << "Short way FOUNDED! Need " << player_.getShortWayLenght() << " steps";
		ofDrawBitmapStringHighlight(reportStr.str(), 100, ofGetWindowHeight() - 100, ofColor::orangeRed, ofColor::black);
	}
}

void Maze::show_in_center()
{
	// Проверяем, создан ли лабиринт
	if (maze_ == nullptr)
		return;
	// Получаем размеры окна
	auto w = ofGetWindowWidth();
	auto h = ofGetWindowHeight();
	// считаем коэффициент соотношения размеров окна к размерам матрици по горизонтали и вертикали соответственно
	auto k = static_cast<float>(w) / maze_.get()->at(0).size();
	auto kh = static_cast<float>(h) / maze_.get()->size();
	// выбираем коэффициент в зависимости от того, какое соотношение меньше
	k = k < kh ? k : kh;
	// Масштаб возьмем равный 75% от размера экрана, чтобы изображение было не до самых краев
	scale_ = k * 0.75;
	// И сместим к центру в зависимости от масштаба
	pos_x_ = (w - maze_.get()->at(0).size() * scale_) / 2;
	pos_y_ = (h - maze_.get()->size() * scale_) / 2;
}

void Maze::setTransparency(int new_alpha, float delay)
{
	Tweener.addTween(alpha_, new_alpha, delay);
}

void Maze::setAlpha(float new_alpha)
{
	alpha_ = new_alpha;
}

void Maze::windowResized(int w, int h)
{
	show_in_center();
}

void Maze::keyPressed(int key)
{
}

void Maze::keyReleased(int key)
{
}

void Maze::mouseDragged(int x, int y, int button)
{
	// При движении мыши с зажатой кнопкой, смещаем изображение на смещение мыши
	pos_x_ -= last_mouse_pos_x_ - x;
	pos_y_ -= last_mouse_pos_y_ - y;
	// И снова запоминаем расположение мыши
	mousePressed(x, y, button);
}

void Maze::mousePressed(int x, int y, int button)
{
	// Запоминаем расположение мыши при нажатии на кнопку
	last_mouse_pos_x_ = x;
	last_mouse_pos_y_ = y;
}

void Maze::mouseReleased(int x, int y, int button)
{
}

void Maze::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
	// Если скролл отрицательный и уменьшение масштаба будет меньше единицы
	if ((scrollY < 0) && (scale_ * 0.9 <= 1.0))
		// То ничего не делаем
		return;
	// Иначе считаем разницу между позицией мыши и смещением лабиринта и делим на масштаб, чтобы определить смещение без масштаба
	auto deltaX = static_cast<double>(x - pos_x_) / scale_;
	auto deltaY = static_cast<double>(y - pos_y_) / scale_;
	// Масштаб увеличиваем в 10/9 в случае положительного скролла и в 0.9 в случае отрицательного
	scale_ *= scrollY < 0 ? 0.9 : 10.0 / 9.0;
	// Высчитываем смещение с новым масштабом
	pos_x_ = x - deltaX * scale_;
	pos_y_ = y - deltaY * scale_;
}
