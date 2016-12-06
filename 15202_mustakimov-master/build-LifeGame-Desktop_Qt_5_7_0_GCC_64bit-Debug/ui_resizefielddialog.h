/********************************************************************************
** Form generated from reading UI file 'resizefielddialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESIZEFIELDDIALOG_H
#define UI_RESIZEFIELDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_ResizeFieldDialog
{
public:
    QFormLayout *formLayout;
    QLabel *labelWidth;
    QLabel *labelHeight;
    QDialogButtonBox *buttonBox;
    QSpinBox *spinBoxHeight;
    QSpinBox *spinBoxWidth;

    void setupUi(QDialog *ResizeFieldDialog)
    {
        if (ResizeFieldDialog->objectName().isEmpty())
            ResizeFieldDialog->setObjectName(QStringLiteral("ResizeFieldDialog"));
        ResizeFieldDialog->resize(234, 110);
        ResizeFieldDialog->setMinimumSize(QSize(234, 110));
        ResizeFieldDialog->setMaximumSize(QSize(234, 110));
        formLayout = new QFormLayout(ResizeFieldDialog);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        labelWidth = new QLabel(ResizeFieldDialog);
        labelWidth->setObjectName(QStringLiteral("labelWidth"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelWidth);

        labelHeight = new QLabel(ResizeFieldDialog);
        labelHeight->setObjectName(QStringLiteral("labelHeight"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelHeight);

        buttonBox = new QDialogButtonBox(ResizeFieldDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(false);

        formLayout->setWidget(4, QFormLayout::FieldRole, buttonBox);

        spinBoxHeight = new QSpinBox(ResizeFieldDialog);
        spinBoxHeight->setObjectName(QStringLiteral("spinBoxHeight"));
        spinBoxHeight->setMinimum(5);
        spinBoxHeight->setMaximum(500);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBoxHeight);

        spinBoxWidth = new QSpinBox(ResizeFieldDialog);
        spinBoxWidth->setObjectName(QStringLiteral("spinBoxWidth"));
        spinBoxWidth->setMinimum(5);
        spinBoxWidth->setMaximum(500);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBoxWidth);

        labelWidth->raise();
        labelHeight->raise();
        buttonBox->raise();
        spinBoxWidth->raise();
        spinBoxHeight->raise();

        retranslateUi(ResizeFieldDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResizeFieldDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResizeFieldDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ResizeFieldDialog);
    } // setupUi

    void retranslateUi(QDialog *ResizeFieldDialog)
    {
        ResizeFieldDialog->setWindowTitle(QApplication::translate("ResizeFieldDialog", "Dialog", 0));
        labelWidth->setText(QApplication::translate("ResizeFieldDialog", "Width:", 0));
        labelHeight->setText(QApplication::translate("ResizeFieldDialog", "Height:", 0));
    } // retranslateUi

};

namespace Ui {
    class ResizeFieldDialog: public Ui_ResizeFieldDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESIZEFIELDDIALOG_H
