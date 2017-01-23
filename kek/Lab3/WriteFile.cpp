#include "WriteFile.h"

WriteToFileHandler::WriteToFileHandler( QWidget * parent = 0 ) 
	: QWidget( parent ) 
	{ 
		FileNameEdit.setFixedSize(200,50); 
		whatToDo.setText("Write the file name you would like to put your field in: ");
		SaveButton.setText("SAVE");
		
		mainLayout.addWidget(&whatToDo);
		mainLayout.addWidget(&FileNameEdit);
		mainLayout.addWidget(&SaveButton);
		mainLayout.setAlignment(&FileNameEdit,Qt::AlignCenter);
		setLayout(&mainLayout);

		connect(&SaveButton,SIGNAL(clicked()),this,SLOT(throwSave()));
	};


void WriteToFileHandler::throwSave()
{
	std::string file_name = FileNameEdit.toPlainText().toLatin1().data();
	emit SaveIntoFile(file_name.c_str());
	return;
}
