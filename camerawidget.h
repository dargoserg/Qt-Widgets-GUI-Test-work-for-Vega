#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QPainter>
#include <QStyleOption>

#include <timerwidget.h>

//#include <QDebug>

class cameraWidget : public QWidget
{
    Q_OBJECT
public:
    explicit cameraWidget(int id, QString name, QWidget *parent = nullptr);

signals:

    void signalSetCurrentCameraWidget(int id);

public slots:

    void slotHidePriorityWidgets();
    void slotShowPriorityWidgets();

    void slotChangeCurrentState(int currentId);
    void slotDeleteCurrentCameraWidget(int currentId);

private slots:
    void slotHideShow();
    void slotChangePriority();
protected:

    int idWidget;
    bool priority;

    QVBoxLayout *mainVLayout;
    timerWidget *timer1;
    timerWidget *timer2;
    QLabel *imageLabel;
    QPushButton *buttonPriority;
    QPushButton *buttonHideShow;

    void addTimerWidgets();
    void hideTimersWidgets();
    void showTimersWidgets();
    void changetCurrentState();

    bool eventFilter(QObject *obj, QEvent *event) override;
    void paintEvent(QPaintEvent *) override;

};

#endif // CAMERAWIDGET_H
