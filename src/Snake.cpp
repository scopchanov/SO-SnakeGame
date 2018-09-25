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

#include "Snake.h"
#include "Dot.h"

Snake::Snake(QObject *parent) :
	QObject(parent)
{
	m_head = createDot(250, 250, DotDirection::DD_Right);

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

	for (int n = m_body.count(); n > 0; n--)
		moveDot(m_body.at(n - 1));
}

void Snake::grow()
{
	Dot *dot = m_body.isEmpty() ? m_head : m_body.last();

	addToBody(dot->xpos(), dot->ypos());
}

void Snake::addToBody(int x, int y)
{
	m_body.append(createDot(x, y, m_body.isEmpty()
							? m_head->direction()
							: m_body.last()->direction()));
}

Dot *Snake::createDot(int x, int y, DotDirection d)
{
	auto *dot = new Dot(this);

	dot->setXpos(x);
	dot->setYpos(y);
	dot->setDirection(d);

	return dot;
}

void Snake::moveDot(Dot *dot)
{
	switch (dot->direction()) {
	case DotDirection::DD_Left:
		dot->setXpos((dot->xpos() - 10) < 0 ? 490 : (dot->xpos() - 10));
		break;
	case DotDirection::DD_Right:
		dot->setXpos((dot->xpos() + 10) > 490 ? 0 : (dot->xpos() + 10));
		break;
	case DotDirection::DD_Up:
		dot->setYpos((dot->ypos() - 10) < 0 ? 490 : (dot->ypos() - 10));
		break;
	case DotDirection::DD_Down:
		dot->setYpos((dot->ypos() + 10) > 490 ? 0 : (dot->ypos() + 10));
		break;
	}

	if (dot != m_head)
		dot->setDirection(dot == m_body.first()
						  ? m_head->direction()
						  : m_body.at(m_body.indexOf(dot) - 1)->direction());
}
