#ifndef SNAKE_H
#define SNAKE_H

#include "Dot.h"

typedef QList<Dot *> DotList;

class Snake : public QObject
{
	Q_OBJECT
public:
	explicit Snake(QObject *parent);

	Dot *head() const;
	DotList body() const;

public slots:
	void slide();
	void grow();

private:
	void addToBody(int x, int y);
	Dot *createDot(int x, int y, Dot::Direction d);
	void moveDot(Dot *dot);

	Dot *m_head;
	DotList m_body;
};

#endif // SNAKE_H
