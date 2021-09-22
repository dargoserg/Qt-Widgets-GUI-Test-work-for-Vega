#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QDebug>
#include <QScrollArea>

#include "camerawidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:

    void signalSetCurrentCameraWidget(int idWidget);
    void signalDeleteCurrentCameraWidget(int idWidget);

    void signalHidePriorityWidgets();
    void signalShowPriorityWidgets();

public slots:

    void slotChangeCurrentWidget(int idWidget);

private slots:

    void slotAddCameraWidget();
    void slotDeleteCurrentCameraWidget();
    void slotShowHidePriorityCameraWidgets();

private:

    Ui::MainWindow *ui;

    int numberCameraWidgets;
    int currentCameraWidget;
    bool hidePriorityWidgets;

    QVBoxLayout *cameraVLayout;
    QPushButton *buttonShowHidePriority;

    void initWindow();


};
#endif // MAINWINDOW_H
