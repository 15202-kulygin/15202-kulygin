#include "mywidget.h"

void MyWidget::paintEvent(QPaintEvent * ) {
	QPainter p(&this);
	p.drawline(0, 0, 100, 100);
}