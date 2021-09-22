#include "timerwidget.h"

timerWidget::timerWidget(bool displayCurrentTime,QWidget *parent) : QLCDNumber(parent)
{
    setSegmentStyle(Flat);

    time = QTime(0,0);
    QTimer *timer = new QTimer(this);

    if (displayCurrentTime)
    {
        connect(timer, &QTimer::timeout,
                this, &timerWidget::slotShowCurrentTime);


        timer->start(1000);
        slotShowCurrentTime();
    }
    else
    {
        connect(timer, &QTimer::timeout,
                this, &timerWidget::slotShowTimer);

        timer->start(1000);
        slotShowTimer();
    }
    resize(150, 60);
}

//Slots

void timerWidget::slotShowCurrentTime()

{
    time = time.currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
    {
        text[2] = ' ';
    }
    display(text);
}

void timerWidget::slotShowTimer()
{
    time = time.addSecs(1);
    QString text = time.toString("mm:ss");

    if ((time.second() % 2) == 0)
    {
        text[2] = ' ';
    }
    display(text);
}

//*Slots
