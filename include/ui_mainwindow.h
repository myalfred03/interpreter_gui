/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "codeeditor.h"
#include "console.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewFile;
    QAction *actionOpen;
    QAction *actionInfoR;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionAbout;
    QAction *actionDocument;
    QAction *actionSave_File;
    QAction *actionRun;
    QAction *actionSetting;
    QAction *actionError_Datos;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QSplitter *splitter_2;
    QSplitter *splitter;
    CodeEditor *editor;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QFrame *line;
    QDoubleSpinBox *doubleSpinBox_3;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_4;
    QCustomPlot *graph_canvas;
    QFrame *line_2;
    QFrame *line_3;
    QComboBox *comboBox;
    QFrame *line_4;
    Console *outputText;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuEdit_O;
    QMenu *menuHelp_H;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(620, 662);
        MainWindow->setWindowTitle(QStringLiteral("Robot Script Editor"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/UNI-Script.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionNewFile = new QAction(MainWindow);
        actionNewFile->setObjectName(QStringLiteral("actionNewFile"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/img/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewFile->setIcon(icon1);
        QFont font;
        font.setFamily(QStringLiteral("Tlwg Mono"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        actionNewFile->setFont(font);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/img/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon2);
        actionInfoR = new QAction(MainWindow);
        actionInfoR->setObjectName(QStringLiteral("actionInfoR"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/img/icon_info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionInfoR->setIcon(icon3);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/img/revoke.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon4);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/img/recovery.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon5);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/img/learning.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon6);
        actionDocument = new QAction(MainWindow);
        actionDocument->setObjectName(QStringLiteral("actionDocument"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/img/information.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDocument->setIcon(icon7);
        actionSave_File = new QAction(MainWindow);
        actionSave_File->setObjectName(QStringLiteral("actionSave_File"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/img/floppy-disk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_File->setIcon(icon8);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName(QStringLiteral("actionRun"));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/img/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRun->setIcon(icon9);
        actionSetting = new QAction(MainWindow);
        actionSetting->setObjectName(QStringLiteral("actionSetting"));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/image/Setting.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSetting->setIcon(icon10);
        actionSetting->setVisible(false);
        actionError_Datos = new QAction(MainWindow);
        actionError_Datos->setObjectName(QStringLiteral("actionError_Datos"));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/img/error.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon11.addFile(QStringLiteral(":/img/error_red.png"), QSize(), QIcon::Active, QIcon::On);
        actionError_Datos->setIcon(icon11);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        splitter_2 = new QSplitter(centralWidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        editor = new CodeEditor(splitter);
        editor->setObjectName(QStringLiteral("editor"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(editor->sizePolicy().hasHeightForWidth());
        editor->setSizePolicy(sizePolicy);
        editor->setMinimumSize(QSize(10, 0));
        editor->setMaximumSize(QSize(800, 800));
        QFont font1;
        font1.setFamily(QStringLiteral("Serif"));
        font1.setPointSize(14);
        editor->setFont(font1);
        editor->setFrameShadow(QFrame::Plain);
        splitter->addWidget(editor);
        gridLayoutWidget = new QWidget(splitter);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(gridLayoutWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 0, 1, 3);

        doubleSpinBox_3 = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_3->setObjectName(QStringLiteral("doubleSpinBox_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox_3->sizePolicy().hasHeightForWidth());
        doubleSpinBox_3->setSizePolicy(sizePolicy1);
        doubleSpinBox_3->setDecimals(3);
        doubleSpinBox_3->setMinimum(-50);
        doubleSpinBox_3->setMaximum(50);
        doubleSpinBox_3->setSingleStep(0.1);

        gridLayout->addWidget(doubleSpinBox_3, 3, 2, 1, 1);

        doubleSpinBox_2 = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox_2->setObjectName(QStringLiteral("doubleSpinBox_2"));
        sizePolicy1.setHeightForWidth(doubleSpinBox_2->sizePolicy().hasHeightForWidth());
        doubleSpinBox_2->setSizePolicy(sizePolicy1);
        doubleSpinBox_2->setDecimals(3);
        doubleSpinBox_2->setMinimum(-50);
        doubleSpinBox_2->setMaximum(50);
        doubleSpinBox_2->setSingleStep(0.1);

        gridLayout->addWidget(doubleSpinBox_2, 3, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setMaximumSize(QSize(16777215, 10));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_3, 2, 2, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(gridLayoutWidget);
        doubleSpinBox->setObjectName(QStringLiteral("doubleSpinBox"));
        sizePolicy1.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
        doubleSpinBox->setSizePolicy(sizePolicy1);
        doubleSpinBox->setDecimals(3);
        doubleSpinBox->setMinimum(-50);
        doubleSpinBox->setMaximum(50);
        doubleSpinBox->setSingleStep(0.1);

        gridLayout->addWidget(doubleSpinBox, 3, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setMaximumSize(QSize(16777215, 10));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 2, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMaximumSize(QSize(16777215, 10));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1);

        pushButton = new QPushButton(gridLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 1, 2, 1, 1);

        pushButton_2 = new QPushButton(gridLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 5, 2, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_4, 9, 0, 1, 3);

        graph_canvas = new QCustomPlot(gridLayoutWidget);
        graph_canvas->setObjectName(QStringLiteral("graph_canvas"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graph_canvas->sizePolicy().hasHeightForWidth());
        graph_canvas->setSizePolicy(sizePolicy3);
        graph_canvas->setMinimumSize(QSize(400, 0));
        graph_canvas->setCursor(QCursor(Qt::CrossCursor));

        gridLayout->addWidget(graph_canvas, 7, 0, 1, 3);

        line_2 = new QFrame(gridLayoutWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 6, 0, 1, 3);

        line_3 = new QFrame(gridLayoutWidget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 8, 0, 1, 3);

        comboBox = new QComboBox(gridLayoutWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 5, 1, 1, 1);

        line_4 = new QFrame(gridLayoutWidget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 0, 0, 1, 3);

        splitter->addWidget(gridLayoutWidget);
        doubleSpinBox_3->raise();
        doubleSpinBox_2->raise();
        label_3->raise();
        label_2->raise();
        pushButton->raise();
        pushButton_2->raise();
        graph_canvas->raise();
        label_4->raise();
        doubleSpinBox->raise();
        label->raise();
        comboBox->raise();
        line->raise();
        line_2->raise();
        line_3->raise();
        line_4->raise();
        splitter_2->addWidget(splitter);
        outputText = new Console(splitter_2);
        outputText->setObjectName(QStringLiteral("outputText"));
        outputText->setMaximumSize(QSize(16777215, 100));
        splitter_2->addWidget(outputText);

        gridLayout_2->addWidget(splitter_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 620, 19));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuEdit_O = new QMenu(menuBar);
        menuEdit_O->setObjectName(QStringLiteral("menuEdit_O"));
        menuHelp_H = new QMenu(menuBar);
        menuHelp_H->setObjectName(QStringLiteral("menuHelp_H"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QFont font2;
        font2.setFamily(QStringLiteral("Tlwg Mono"));
        mainToolBar->setFont(font2);
        mainToolBar->setAutoFillBackground(true);
        mainToolBar->setIconSize(QSize(18, 18));
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuEdit_O->menuAction());
        menuBar->addAction(menuHelp_H->menuAction());
        menu->addAction(actionNewFile);
        menu->addAction(actionOpen);
        menu->addAction(actionSave_File);
        menuEdit_O->addAction(actionInfoR);
        menuEdit_O->addAction(actionUndo);
        menuEdit_O->addAction(actionRedo);
        menuHelp_H->addAction(actionAbout);
        menuHelp_H->addAction(actionDocument);
        mainToolBar->addAction(actionNewFile);
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave_File);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);
        mainToolBar->addAction(actionRun);
        mainToolBar->addAction(actionSetting);
        mainToolBar->addAction(actionInfoR);
        mainToolBar->addAction(actionError_Datos);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionNewFile->setText(QApplication::translate("MainWindow", "Nuevo", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionNewFile->setToolTip(QApplication::translate("MainWindow", "Crear nuevo archivo Script LVR", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionNewFile->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "Abrir", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionOpen->setToolTip(QApplication::translate("MainWindow", "Abrir Archivo Script LVR", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionInfoR->setText(QApplication::translate("MainWindow", "Info", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionInfoR->setToolTip(QApplication::translate("MainWindow", "Informaci\303\263n del Robot Cargado a ROS", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionInfoR->setShortcut(QApplication::translate("MainWindow", "Ctrl+A", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionUndo->setText(QApplication::translate("MainWindow", "Atras", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("MainWindow", "Adelante", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionAbout->setText(QApplication::translate("MainWindow", "About Editor", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionAbout->setToolTip(QApplication::translate("MainWindow", "\345\205\263\344\272\216 HJ Editor", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionDocument->setText(QApplication::translate("MainWindow", "Documentaci\303\263n", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionDocument->setToolTip(QApplication::translate("MainWindow", "Ver documentaci\303\263n", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionSave_File->setText(QApplication::translate("MainWindow", "Guardar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSave_File->setToolTip(QApplication::translate("MainWindow", "Guardar Archivo ", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionSave_File->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionRun->setText(QApplication::translate("MainWindow", "Ejecutar", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionRun->setToolTip(QApplication::translate("MainWindow", "Ejecutar Simulaci\303\263n", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionRun->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionSetting->setText(QApplication::translate("MainWindow", "Setting", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionSetting->setToolTip(QApplication::translate("MainWindow", "\346\233\264\346\224\271\347\274\226\350\276\221\345\231\250\347\232\204\350\256\276\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionError_Datos->setText(QApplication::translate("MainWindow", "Error", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionError_Datos->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Este icono se activara si se ingreso un par\303\241metro al robot fuera de su espacio de trabajo.</p><p>Favor Leer la Hoja de Datos del robot a controlar.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("MainWindow", "D", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "I", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "P", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Send Value PID", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Clear Graph", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "X/Y", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Show All Joints", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Show Joint 6", Q_NULLPTR)
        );
        menu->setTitle(QApplication::translate("MainWindow", "Archivo", Q_NULLPTR));
        menuEdit_O->setTitle(QApplication::translate("MainWindow", "Editar", Q_NULLPTR));
        menuHelp_H->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
