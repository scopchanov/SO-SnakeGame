/**
MIT License

Copyright (c) 2018 Michael Scopchanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "mainwindow.h"
#include "Snake.h"
#include "Dot.h"
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	m_snake(new Snake(this)),
	m_pending(0)
{
	auto *timer = new QTimer(this);

	timer->start(100);

	setFixedSize(500, 500);
	setWindowTitle("Snake game");

	connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
}

void MainWindow::paintEvent(QPaintEvent * /*event*/)
{
	QPainter painter(this);

	painter.drawRect(0, 0, 500, 500);
	painter.fillRect(0, 0, 500, 500, "#F0F1F2");

	painter.setPen(Qt::darkGreen);
	painter.setBrush(Qt::green);

	foreach (Dot *dot, m_snake->body())
		painter.drawEllipse(dot->xpos(),
							dot->ypos(), 10, 10);

	painter.setPen(Qt::red);
	painter.setBrush(Qt::red);
	painter.drawEllipse(m_snake->head()->xpos(),
						m_snake->head()->ypos(), 10, 10);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	m_pending = event->key();
}

bool MainWindow::hasCollision() const
{
	Dot *head = m_snake->head();
	bool collision = false;

	foreach (Dot *dot, m_snake->body())
		collision |= (dot->xpos() == head->xpos())
					 && (dot->ypos() == head->ypos());

	return collision;
}

void MainWindow::on_timeout()
{
	Dot *head = m_snake->head();

	switch (m_pending) {
	case Qt::Key_Left:
		if (head->direction() != DotDirection::DD_Right)
			head->setDirection(DotDirection::DD_Left);
		break;
	case Qt::Key_Right:
		if (head->direction() != DotDirection::DD_Left)
			head->setDirection(DotDirection::DD_Right);
		break;
	case Qt::Key_Up:
		if (head->direction() != DotDirection::DD_Down)
			head->setDirection(DotDirection::DD_Up);
		break;
	case Qt::Key_Down:
		if (head->direction() != DotDirection::DD_Up)
			head->setDirection(DotDirection::DD_Down);
		break;
	}

	m_pending = 0;
	m_snake->slide();
	update();

	if (hasCollision())
		static_cast<QTimer *>(sender())->stop();
}
