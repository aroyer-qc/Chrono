//-------------------------------------------------------------------------------------------------
//
// Copyright(c) 2025 Alain Royer.
// Email: aroyer.qc@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
// AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//-------------------------------------------------------------------------------------------------

#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include "counter.h"

//*************************************************************************************************

MainWindow::MainWindow(const QString& ImagePath)
{
    StartFlag = 0;

    QLabel* backgroundLabel = new QLabel(this);     // Parent is MainWindow
    backgroundLabel->setPixmap(QPixmap(ImagePath));
    backgroundLabel->lower(); // Push it below all other widgets
    backgroundLabel->show();

    Counter* Counting = new Counter;
    Counting->moveToThread(&CounterThread);
    connect(Counting, &Counter::ResultReady, this, &MainWindow::CounterFinish);
    connect(this, &MainWindow::StartChronometer, Counting, &Counter::StartChronometer);
    connect(this, &MainWindow::ResetChronometer, Counting, &Counter::ResetChronometer);
    connect(&CounterThread, &QThread::finished, &CounterThread, &QObject::deleteLater);

    CounterThread.start();

    // Set the window flags to remove frame and make the window transparent
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setAttribute(Qt::WA_TranslucentBackground);

    // Create button
    buttonStart = new QPushButton(" Start", this);
    buttonLap = new QPushButton(" Lap ", this);
    buttonReset = new QPushButton("Reset", this);

    // Set the icon for the button
    buttonStart->setIcon(QIcon(":/icons/Ressource/start.png"));
    buttonLap->setIcon(QIcon(":/icons/Ressource/lap.png"));
    buttonReset->setIcon(QIcon(":/icons/Ressource/reset.png"));

    // Set the button's styles
    QString ButtonStyle = "QPushButton {"
                          "background-color: transparent;" // Makes the button transparent
                          "color: white;"                  // Sets text color to white
                          "border: none;"                  // Removes any border
                          "}"
                          "QPushButton:pressed {"
                          "   color: lightgray;"           // Change text color to white when pressed
                          "}";
    buttonStart->setStyleSheet(ButtonStyle);
    buttonLap->setStyleSheet(ButtonStyle);
    buttonReset->setStyleSheet(ButtonStyle);

    buttonStart->resize(60, 20);
    buttonStart->move(47, 127);

    buttonLap->resize(60, 20);
    buttonLap->move(122, 127);

    buttonReset->resize(60, 20);
    buttonReset->move(194, 127);

    // Connect button to an action
    connect(buttonStart, &QPushButton::clicked, this, &MainWindow::onButtonStartClicked);
    connect(buttonLap, &QPushButton::clicked, this, &MainWindow::onButtonLapClicked);
    connect(buttonReset, &QPushButton::clicked, this, &MainWindow::onButtonResetClicked);

    QString StyleSheet("font-family: 'DS-Digital'; font-size: 48px; font-style: italic; font-weight: bold; color: #202020;");

    labelStaticLCD_100_Min = new QLabel("8", this);
    labelStaticLCD_100_Min->setStyleSheet(StyleSheet);
    labelStaticLCD_100_Min->move(48, 62);

    labelStaticLCD_10_Min = new QLabel("8", this);
    labelStaticLCD_10_Min->setStyleSheet(StyleSheet);
    labelStaticLCD_10_Min->move(73, 62);

    labelStaticLCD_1_Min = new QLabel("8", this);
    labelStaticLCD_1_Min->setStyleSheet(StyleSheet);
    labelStaticLCD_1_Min->move(98, 62);

    labelStaticLCD_10_Sec = new QLabel("8", this);
    labelStaticLCD_10_Sec->setStyleSheet(StyleSheet);
    labelStaticLCD_10_Sec->move(138, 62);

    labelStaticLCD_1_Sec = new QLabel("8", this);
    labelStaticLCD_1_Sec->setStyleSheet(StyleSheet);
    labelStaticLCD_1_Sec->move(163, 62);

    labelStaticLCD_10_HundredSEC = new QLabel("8", this);
    labelStaticLCD_10_HundredSEC->setStyleSheet(StyleSheet);
    labelStaticLCD_10_HundredSEC->move(203, 62);

    labelStaticLCD_1_HundredSEC = new QLabel("8", this);
    labelStaticLCD_1_HundredSEC->setStyleSheet(StyleSheet);
    labelStaticLCD_1_HundredSEC->move(228, 62);

    StyleSheet = ("background-color: transparent; font-family: 'DS-Digital'; font-style: italic; font-size: 48px; font-weight: bold; color: white;");

    labelLCD_100_Min = new QLabel(" ", this);
    labelLCD_100_Min->setStyleSheet(StyleSheet);
    labelLCD_100_Min->resize(24, 48);
    labelLCD_100_Min->raise();

    labelLCD_10_Min = new QLabel(" ", this);
    labelLCD_10_Min->setStyleSheet(StyleSheet);
    labelLCD_10_Min->resize(24, 48);
    labelLCD_10_Min->raise();

    labelLCD_1_Min = new QLabel("1", this);
    labelLCD_1_Min->setStyleSheet(StyleSheet);
    labelLCD_1_Min->resize(24, 48);
    labelLCD_1_Min->raise();

    labelLCD_10_Sec = new QLabel("0", this);
    labelLCD_10_Sec->setStyleSheet(StyleSheet);
    labelLCD_10_Sec->resize(24, 48);
    labelLCD_10_Sec->raise();

    labelLCD_1_Sec = new QLabel("0", this);
    labelLCD_1_Sec->setStyleSheet(StyleSheet);
    labelLCD_1_Sec->resize(24, 48);
    labelLCD_1_Sec->raise();

    labelLCD_10_HundredSEC = new QLabel("0", this);
    labelLCD_10_HundredSEC->setStyleSheet(StyleSheet);
    labelLCD_10_HundredSEC->resize(24, 48);
    labelLCD_10_HundredSEC->raise();

    labelLCD_1_HundredSEC = new QLabel("0", this);
    labelLCD_1_HundredSEC->setStyleSheet(StyleSheet);
    labelLCD_1_HundredSEC->resize(24, 48);
    labelLCD_1_HundredSEC->raise();

    ResetLCD();
    
    // Lap Window
    LapWindowFlag = 0;
    LapWindow = new class LapWindow(this);
    LapWindow->setWindowFlags(Qt::Widget | Qt::FramelessWindowHint);
    LapWindow->move(QPoint(0, 0));
    LapWindow->show();                                          // Ensure LapWindow is visible
    LapWindow->lower();
    connect(LapWindow, &LapWindow::HideLapWindow, this, &MainWindow::HideLapWindow);

    // Add the reset lap button to the child window
    QPushButton* ButtonResetLapHistory = new QPushButton("Reset Lap History", LapWindow);
    ButtonResetLapHistory->setStyleSheet(ButtonStyle);
    ButtonResetLapHistory->setIcon(QIcon(":/icons/Ressource/reset.png"));
    ButtonResetLapHistory->resize(140, 20);
    ButtonResetLapHistory->move(60, 129); // Position button within the child window
    connect(ButtonResetLapHistory, &QPushButton::clicked, this, &MainWindow::onButtonResetLapHistoryClicked);
}

//*************************************************************************************************

MainWindow::~MainWindow()
{
    CounterThread.quit();
    CounterThread.wait();
}

//*************************************************************************************************

// Public method to get background image
const QPixmap MainWindow::getBackgroundImage()
{
    return BackgroundImage;
}

//*************************************************************************************************

void MainWindow::ResetLCD()
{
    UpdateLCD("  0:00:00");
}

//*************************************************************************************************

void MainWindow::UpdateLCD(QString Data)
{
    // this function fix bad offset into the DS_Digital Font for number 1
    labelLCD_100_Min->move(Data.at(0) == '1' ? 60 : 48, 62);
    labelLCD_10_Min->move(Data.at(1) == '1' ? 85 : 73, 62);
    labelLCD_1_Min->move(Data.at(2) == '1' ? 110 : 98, 62);
    labelLCD_10_Sec->move(Data.at(4) == '1' ? 150 : 138, 62);
    labelLCD_1_Sec->move(Data.at(5) == '1' ? 175 : 163, 62);
    labelLCD_10_HundredSEC->move(Data.at(7) == '1' ? 215 : 203, 62);
    labelLCD_1_HundredSEC->move(Data.at(8) == '1' ? 240 : 228, 62);
    labelLCD_100_Min->setText(Data.at(0));
    labelLCD_10_Min->setText(Data.at(1));
    labelLCD_1_Min->setText(Data.at(2));
    labelLCD_10_Sec->setText(Data.at(4));
    labelLCD_1_Sec->setText(Data.at(5));
    labelLCD_10_HundredSEC->setText(Data.at(7));
    labelLCD_1_HundredSEC->setText(Data.at(8));
    LapTime = Data;
}

//*************************************************************************************************

void MainWindow::paintEvent(QPaintEvent* Event)
{
    Q_UNUSED(Event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, BackgroundImage);                  // Draw the background image
    LapWindow->stackUnder(this);
}

//*************************************************************************************************

void MainWindow::mousePressEvent(QMouseEvent* Event)
{
    if(Event->button() == Qt::LeftButton)                       // Allow dragging the window by clicking anywhere
    {
        dragPosition = (Event->globalPosition().toPoint() - frameGeometry().topLeft());
        Event->accept();
    }
}

//*************************************************************************************************

void MainWindow::mouseMoveEvent(QMouseEvent* Event)
{
    if(Event->buttons() & Qt::LeftButton)                       // Handle dragging the window
    {
        move(Event->globalPosition().toPoint() - dragPosition);
        Event->accept();
    }
}

//*************************************************************************************************

void MainWindow::onButtonStartClicked()
{
    if(StartFlag == 0)
    {
        buttonStart->setIcon(QIcon(":/icons/Ressource/stop.png"));
        buttonStart->setText("Stop");
        emit StartChronometer();
        StartFlag = 1;
        StopFlag = 1;
    }
    else
    {
        buttonStart->setIcon(QIcon(":/icons/Ressource/start.png"));
        buttonStart->setText("Start");
        emit StartChronometer();
        StartFlag = 0;
        StopFlag = 0;
    }
}

//*************************************************************************************************

void MainWindow::onButtonLapClicked()
{
    LapWindow->AddLapTime(LapTime);

    if(LapWindowFlag == 0)
    {
        QPoint CurrentPosition = LapWindow->pos();                                      // Get the current position of the widget
        QPropertyAnimation* animation = new QPropertyAnimation(LapWindow, "pos");
        animation->setDuration(1000);                                                   // Animation duration in milliseconds

        animation->setStartValue(CurrentPosition);                                      // Starting position
        animation->setEndValue(QPoint(CurrentPosition.x(),
                                      CurrentPosition.y() + 180));                        // Ending position (on-screen)
        animation->start(QAbstractAnimation::DeleteWhenStopped);                        // Automatically delete when finished
        LapWindowFlag = 1;
    }
}

//*************************************************************************************************
void MainWindow::HideLapWindow()
{
    if(LapWindowFlag == 1)
    {
        QPoint CurrentPosition = LapWindow->pos();                                      // Get the current position of the widget
        QPropertyAnimation* animation = new QPropertyAnimation(LapWindow, "pos");
        animation->setDuration(1000);                                                   // Animation duration in milliseconds

        animation->setStartValue(CurrentPosition);                            // Starting position
        animation->setEndValue(QPoint(CurrentPosition.x(),
                                      CurrentPosition.y() - 180));                        // Ending position (on-screen)
        animation->start(QAbstractAnimation::DeleteWhenStopped);                        // Automatically delete when finished
        LapWindowFlag = 0;
    }
}

//*************************************************************************************************

void MainWindow::onButtonResetClicked()
{
    ResetLCD();
    emit ResetChronometer();
}

//*************************************************************************************************

void MainWindow::onButtonResetLapHistoryClicked()
{
    LapWindow->ClearLaps();
}

//*************************************************************************************************

void MainWindow::CounterFinish(QString data)
{
    UpdateLCD(data);

    if(StartFlag == 1)
    {
        emit StartChronometer();
    }
}

//*************************************************************************************************

