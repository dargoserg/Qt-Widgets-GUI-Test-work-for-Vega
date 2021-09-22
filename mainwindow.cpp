#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initWindow();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWindow()
{

    this->setStyleSheet("background-color:rgb(49, 54, 58);"
                        "border-width: 2px;"
                        "border-style: solid;"
                        "border-color: rgb(49, 54, 58);");

    numberCameraWidgets = 0;
    hidePriorityWidgets = true;

    QPushButton *buttonAddCameraWidget = new QPushButton(this);
    connect( buttonAddCameraWidget, &QPushButton::clicked,
             this, &MainWindow::slotAddCameraWidget);
    buttonAddCameraWidget->setIcon(QIcon(":/res/ico/64x64/plus.ico"));
    buttonAddCameraWidget->setIconSize(QSize(32,32));
    buttonAddCameraWidget->setMinimumSize(32,32);

    QPushButton *buttonDeleteSelectedCameraWidget = new QPushButton(this);
    connect( buttonDeleteSelectedCameraWidget, &QPushButton::clicked,
             this, &MainWindow::slotDeleteCurrentCameraWidget);
    buttonDeleteSelectedCameraWidget->setIcon(QIcon(":/res/ico/64x64/trash.ico"));
    buttonDeleteSelectedCameraWidget->setIconSize(QSize(32,32));
    buttonDeleteSelectedCameraWidget->setMinimumSize(32,32);

    buttonShowHidePriority = new QPushButton(this);
    connect( buttonShowHidePriority, &QPushButton::clicked,
             this, &MainWindow::slotShowHidePriorityCameraWidgets);
    buttonShowHidePriority->setIcon(QIcon(":/res/ico/64x64/star.ico"));
    buttonShowHidePriority->setIconSize(QSize(32,32));
    buttonShowHidePriority->setMinimumSize(32,32);

    QHBoxLayout *topButtonMenuHLayout = new QHBoxLayout();
    topButtonMenuHLayout->addWidget(buttonAddCameraWidget);
    topButtonMenuHLayout->addWidget(buttonDeleteSelectedCameraWidget);
    topButtonMenuHLayout->addWidget(buttonShowHidePriority);
    topButtonMenuHLayout->addStretch();

    cameraVLayout = new QVBoxLayout();
    cameraVLayout->addStretch(1);

    QWidget *widgetForScroll = new QWidget(this);
    widgetForScroll->setLayout(cameraVLayout);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetForScroll);
    scrollArea->setStyleSheet("border-style: solid;"
                              "border-color: white;"
                              "border-width: 1px;"
                              "border-radius: 3px");

    QVBoxLayout *mainVLayout = new QVBoxLayout();
    mainVLayout->addLayout(topButtonMenuHLayout);
    mainVLayout->addWidget(scrollArea);

    this->centralWidget()->setLayout(mainVLayout);

    slotAddCameraWidget();
}

//Functions

void MainWindow::slotAddCameraWidget()
{
    numberCameraWidgets++;
    QString cameraNameString = "Видеокамера (ББП-" + QString::number(numberCameraWidgets) + ")";
    cameraWidget *newCameraWidget = new cameraWidget(numberCameraWidgets,cameraNameString,this);

    connect(this, &MainWindow::signalSetCurrentCameraWidget,
            newCameraWidget, &cameraWidget::slotChangeCurrentState);

    connect(newCameraWidget, &cameraWidget::signalSetCurrentCameraWidget,
            this, &MainWindow::slotChangeCurrentWidget);

    connect(this, &MainWindow::signalDeleteCurrentCameraWidget,
            newCameraWidget, &cameraWidget::slotDeleteCurrentCameraWidget);

    connect(this, &MainWindow::signalHidePriorityWidgets,
            newCameraWidget, &cameraWidget::slotHidePriorityWidgets);

    connect(this, &MainWindow::signalShowPriorityWidgets,
            newCameraWidget, &cameraWidget::slotShowPriorityWidgets);

    cameraVLayout->insertWidget(cameraVLayout->count()-1,newCameraWidget);

}

//*Functions

//Slots

void MainWindow::slotChangeCurrentWidget(int idWidget)
{
    if (currentCameraWidget == idWidget)
    {
        currentCameraWidget = 0;
        emit signalSetCurrentCameraWidget(currentCameraWidget);
    }
    else
    {
        currentCameraWidget = idWidget;
        emit signalSetCurrentCameraWidget(currentCameraWidget);
    }
}

void MainWindow::slotDeleteCurrentCameraWidget()
{
    if (currentCameraWidget == 0)
    {

    }
    else
    {
        emit signalDeleteCurrentCameraWidget(currentCameraWidget);
    }
}

void MainWindow::slotShowHidePriorityCameraWidgets()
{
    if (hidePriorityWidgets)
    {
        hidePriorityWidgets = false;
        emit signalShowPriorityWidgets();
        buttonShowHidePriority->setIcon(QIcon(":/res/ico/64x64/fill_star.ico"));
    }
    else
    {
        hidePriorityWidgets = true;
        emit signalHidePriorityWidgets();
        buttonShowHidePriority->setIcon(QIcon(":/res/ico/64x64/star.ico"));
    }
}

//*Slots
