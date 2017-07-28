#ifndef DOT_H
#define DOT_H

#include <QObject>

class Dot : public QObject
{
	Q_OBJECT
public:
	enum Direction { LEFT = 0, RIGHT, UP, DOWN };

	explicit Dot(QObject *parent);

	int xpos() const;
	void setXpos(int x);
	int ypos() const;
	void setYpos(int y);
	Direction direction() const;
	void setDirection(Direction d);

private:
	int m_xpos, m_ypos;
	Direction m_direction; // Direction of the particular dot.
};

#endif // DOT_H
