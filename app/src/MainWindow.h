#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include "Snake.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	explicit MainWindow(QWidget *parent = nullptr);

protected:
	void paintEvent(QPaintEvent*);
	void keyPressEvent(QKeyEvent* event);

private:
	bool hasCollision() const;

	Snake *m_snake;
	int m_pending = 0;

private slots:
	void on_timeout();
};

#endif // MAINWINDOW_H
