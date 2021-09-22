#include "camerawidget.h"

cameraWidget::cameraWidget(int id, QString name, QWidget *parent) : QWidget(parent)
{
    cameraWidget::setStyleSheet("background-color:rgb(68, 68, 68);"
                                "border-width: 1px;"
                                "border-style: solid;"
                                "border-color: white;"
                                "border-radius: 3px;"
                                "font-size: 20px;"
                                "color:white;");
    idWidget = id;
    priority = false;

    QPushButton *buttonLocation = new QPushButton(this);
    buttonLocation->setDisabled(true);
    buttonLocation->setIcon(QIcon(":/res/ico/64x64/locate_gps.ico"));
    buttonLocation->setIconSize(QSize(24,24));
    buttonLocation->setMinimumSize(32,32);
    buttonLocation->setStyleSheet("border-width: 0px;");

    buttonPriority = new QPushButton(this);
    connect (buttonPriority, &QPushButton::clicked,
             this, &cameraWidget::slotChangePriority);
    buttonPriority->setIcon(QIcon(":/res/ico/64x64/star.ico"));
    buttonPriority->setIconSize(QSize(32,32));
    buttonPriority->setMinimumSize(32,32);
    buttonPriority->setStyleSheet("border-width: 0px;");

    buttonHideShow = new QPushButton(this);
    connect (buttonHideShow, &QPushButton::clicked,
             this, &cameraWidget::slotHideShow);
    buttonHideShow->setIcon(QIcon(":/res/ico/64x64/up_arrow.ico"));
    buttonHideShow->setIconSize(QSize(32,32));
    buttonHideShow->setMinimumSize(32,32);
    buttonHideShow->setStyleSheet("border-width: 0px;");

    QLabel *labelName = new QLabel(name,this);
    labelName->setStyleSheet("border-width: 0px;");

    QHBoxLayout *topButtonMenuHLayout = new QHBoxLayout();
    topButtonMenuHLayout->addWidget(buttonLocation);
    topButtonMenuHLayout->addWidget(labelName);
    topButtonMenuHLayout->addStretch();
    topButtonMenuHLayout->addWidget(buttonPriority);
    topButtonMenuHLayout->addWidget(buttonHideShow);

    mainVLayout = new QVBoxLayout(this);
    mainVLayout->addLayout(topButtonMenuHLayout);
    mainVLayout->addStretch();

    addTimerWidgets();
    hideTimersWidgets();

    this->installEventFilter(this);
    //qDebug() <<mainVLayout->findChildren<QHBoxLayout*>();
}

//Functions

void cameraWidget::addTimerWidgets()
{
    timer1 = new timerWidget(false,this);
    timer1->setStyleSheet("border-width: 0px;");

    timer2 = new timerWidget(true,this);
    timer2->setStyleSheet("border-width: 0px;");

    imageLabel = new QLabel(this);
    imageLabel->setPixmap(QPixmap(":/res/ico/No_Signal.png"));

    QHBoxLayout *timersHLayout = new QHBoxLayout();
    timersHLayout->addStretch();
    timersHLayout->addWidget(timer1);
    timersHLayout->addWidget(imageLabel);
    timersHLayout->addWidget(timer2);
    timersHLayout->addStretch();

    mainVLayout->addLayout(timersHLayout);
}

void cameraWidget::changetCurrentState()
{
    emit signalSetCurrentCameraWidget(idWidget);
}

void cameraWidget::hideTimersWidgets()
{
    buttonHideShow->setIcon(QIcon(":/res/ico/64x64/down_arrow.ico"));
    timer1->hide();
    timer2->hide();
    imageLabel->hide();
}

void cameraWidget::showTimersWidgets()
{
    buttonHideShow->setIcon(QIcon(":/res/ico/64x64/up_arrow.ico"));
    timer1->show();
    timer2->show();
    imageLabel->show();
}

//Functions*

//Slots

void cameraWidget::slotChangePriority()
{
    if (priority)
    {
        buttonPriority->setIcon(QIcon(":/res/ico/64x64/star.ico"));
        priority = false;
    }
    else
    {
        buttonPriority->setIcon(QIcon(":/res/ico/64x64/fill_star.ico"));
        priority = true;
    }
}


void cameraWidget::slotHideShow()
{
    if (timer1->isHidden())
    {
        showTimersWidgets();
    }
    else
    {
        hideTimersWidgets();
    }
}

void cameraWidget::slotHidePriorityWidgets()
{
    if (priority)
    {
        hideTimersWidgets();
    }
}

void cameraWidget::slotShowPriorityWidgets()
{
    if (priority)
    {
        showTimersWidgets();
    }
}

void cameraWidget::slotDeleteCurrentCameraWidget(int currentId)
{
    if (currentId == idWidget) this->deleteLater();
}

void cameraWidget::slotChangeCurrentState(int currentId)
{
    if (currentId == idWidget)
    {
        cameraWidget::setStyleSheet("background-color:rgb(13, 87, 126);"
                                    "border-width: 1px;"
                                    "border-style: solid;"
                                    "border-color: white;"
                                    "border-radius: 3px;"
                                    "font-size: 20px;"
                                    "color:white");
    }
    else
    {
        cameraWidget::setStyleSheet("background-color:rgb(68, 68, 68);"
                                    "border-width: 1px;"
                                    "border-style: solid;"
                                    "border-color: white;"
                                    "border-radius: 3px;"
                                    "font-size: 20px;"
                                    "color:white");
    }
}


//*Slots

//QtMagic

void cameraWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

bool cameraWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        changetCurrentState();
        return true;
    }
    else return false;
}

//*QtMagic









