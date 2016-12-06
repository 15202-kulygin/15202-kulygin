#ifndef RESIZEFIELDDIALOG_H
#define RESIZEFIELDDIALOG_H

#include <QDialog>

#include "ui_resizefielddialog.h"

namespace Ui {
class ResizeFieldDialog;
}

class ResizeFieldDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResizeFieldDialog(QWidget *parent = 0);
    ~ResizeFieldDialog();

    void setInputWidth(int width)
    {
        ui->spinBoxWidth->setValue(width);
    }

    void setInputHeight(int height)
    {
        ui->spinBoxHeight->setValue(height);
    }

    int getInputWidth()
    {
        return ui->spinBoxWidth->value();
    }

    int getInputHeight()
    {
        return ui->spinBoxHeight->value();
    }

private:
    Ui::ResizeFieldDialog *ui;
};

#endif // RESIZEFIELDDIALOG_H
