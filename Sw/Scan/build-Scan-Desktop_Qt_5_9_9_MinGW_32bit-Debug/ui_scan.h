/********************************************************************************
** Form generated from reading UI file 'scan.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCAN_H
#define UI_SCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Scan
{
public:

    void setupUi(QWidget *Scan)
    {
        if (Scan->objectName().isEmpty())
            Scan->setObjectName(QStringLiteral("Scan"));
        Scan->resize(800, 600);

        retranslateUi(Scan);

        QMetaObject::connectSlotsByName(Scan);
    } // setupUi

    void retranslateUi(QWidget *Scan)
    {
        Scan->setWindowTitle(QApplication::translate("Scan", "Scan", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Scan: public Ui_Scan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCAN_H
