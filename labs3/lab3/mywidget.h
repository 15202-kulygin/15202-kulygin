#include <QtGui/Qwidget>

//qmake -project && qmake && make

class MyWidget : public QWidget {
	Q_OBJECT	
	protected:
	void paintEvent(QPaintEvent * event) override;

	void mouseMoveEvent(QPaintEvent * event) override;
};