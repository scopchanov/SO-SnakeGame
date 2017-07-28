#include "Snake.h"

Snake::Snake(QObject *parent) : QObject(parent)
{
	m_head = createDot(250, 250, Dot::Direction::RIGHT);

	addToBody(240, 250);
	addToBody(230, 250);
	addToBody(220, 250);
	addToBody(210, 250);
	addToBody(200, 250);
}

Dot *Snake::head() const
{
	return m_head;
}

DotList Snake::body() const
{
	return m_body;
}

void Snake::slide()
{
	moveDot(m_head);

	for (int n = m_body.count(); n > 0; n--) { moveDot(m_body.at(n - 1)); }
}

void Snake::grow()
{
	Dot *dot = m_body.isEmpty() ? m_head : m_body.last();

	addToBody(dot->xpos(), dot->ypos());
}

void Snake::addToBody(int x, int y)
{
	m_body.append(createDot(x, y, m_body.isEmpty() ? m_head->direction() : m_body.last()->direction()));
}

Dot *Snake::createDot(int x, int y, Dot::Direction d)
{
	Dot *dot = new Dot(this);

	dot->setXpos(x);
	dot->setYpos(y);
	dot->setDirection(d);

	return dot;
}

void Snake::moveDot(Dot *dot)
{
	switch (dot->direction())
	{
		case Dot::Direction::LEFT:
			dot->setXpos((dot->xpos() - 10) < 0 ? 490 : (dot->xpos() - 10));
			break;
		case Dot::Direction::RIGHT:
			dot->setXpos((dot->xpos() + 10) > 490 ? 0 : (dot->xpos() + 10));
			break;
		case Dot::Direction::UP:
			dot->setYpos((dot->ypos() - 10) < 0 ? 490 : (dot->ypos() - 10));
			break;
		case Dot::Direction::DOWN:
			dot->setYpos((dot->ypos() + 10) > 490 ? 0 : (dot->ypos() + 10));
			break;
	}

	if (dot != m_head) { dot->setDirection(dot == m_body.first() ? m_head->direction() : m_body.at(m_body.indexOf(dot) - 1)->direction()); }
}
