#ifndef _WRITE_TO_FILE_WIDGET_
#define _WRITE_TO_FILE_WIDGET_

#include <fstream>
#include <QtGui>
#include <string>

class WriteToFileHandler: public QWidget
{
	Q_OBJECT
public:	
	WriteToFileHandler( QWidget * parent );

public slots:
	void Write() { this->show(); };

signals:
	void SaveIntoFile(std::string);

private slots:
	void throwSave();

private:
	QVBoxLayout mainLayout;
	QLabel whatToDo;
	QTextEdit FileNameEdit;
	QPushButton SaveButton;
};


#endif