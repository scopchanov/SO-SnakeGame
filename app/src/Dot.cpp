#include "Dot.h"

Dot::Dot(QObject *parent) : QObject(parent)
{

}

int Dot::xpos() const
{
	return m_xpos;
}

void Dot::setXpos(int x)
{
	m_xpos = x;
}

int Dot::ypos() const
{
	return m_ypos;
}

void Dot::setYpos(int y)
{
	m_ypos = y;
}

Dot::Direction Dot::direction() const
{
	return m_direction;
}

void Dot::setDirection(Dot::Direction d)
{
	m_direction = d;
}
