#ifndef TIMERWIDGET_H
#define TIMERWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QTime>

#include <QLCDNumber>

class timerWidget : public QLCDNumber
{
    Q_OBJECT
public:
    explicit timerWidget(bool displayCurrentTime = false, QWidget *parent = nullptr);

private slots:

    void slotShowCurrentTime();
    void slotShowTimer();

private:

    QTime time;

};

#endif // TIMERWIDGET_H
