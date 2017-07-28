#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	QTimer* timer = new QTimer(this);

	m_snake = new Snake(this);
	timer->start(100);

	resize(500, 500);
	setWindowTitle("Snake game");

	connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
}

void MainWindow::paintEvent(QPaintEvent*)
{
	QPainter painter(this);

	painter.drawRect(0, 0, 500, 500);
	painter.fillRect(0, 0, 500, 500, Qt::black);

	painter.setPen(Qt::green);
	painter.setBrush(Qt::green);

	foreach (Dot *dot, m_snake->body()) { painter.drawEllipse(dot->xpos(), dot->ypos(), 10, 10); }

	painter.setPen(Qt::red);
	painter.setBrush(Qt::red);
	painter.drawEllipse(m_snake->head()->xpos(), m_snake->head()->ypos(), 10, 10);
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
	m_pending = event->key();
}

bool MainWindow::hasCollision() const
{
	Dot *head = m_snake->head();
	bool collision = false;

	foreach (Dot *dot, m_snake->body()) { collision |= (dot->xpos() == head->xpos()) && (dot->ypos() == head->ypos()); }

	return collision;
}

void MainWindow::on_timeout()
{
	Dot *head = m_snake->head();

	switch (m_pending)
	{
		case Qt::Key_Left:
			if (head->direction() != Dot::Direction::RIGHT) { head->setDirection(Dot::Direction::LEFT); }
			break;
		case Qt::Key_Right:
			if (head->direction() != Dot::Direction::LEFT) { head->setDirection(Dot::Direction::RIGHT); }
			break;
		case Qt::Key_Up:
			if (head->direction() != Dot::Direction::DOWN) { head->setDirection(Dot::Direction::UP); }
			break;
		case Qt::Key_Down:
			if (head->direction() != Dot::Direction::UP) { head->setDirection(Dot::Direction::DOWN); }
			break;
	}

	m_pending = 0;
	m_snake->slide();
	update();
	if (hasCollision()) { static_cast<QTimer *>(sender())->stop(); }
}
