#include "resizefielddialog.h"
#include "ui_resizefielddialog.h"

ResizeFieldDialog::ResizeFieldDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResizeFieldDialog)
{
    ui->setupUi(this);
}

ResizeFieldDialog::~ResizeFieldDialog()
{
    delete ui;
}
