#include <QWidget>
#include <QPainter>
#include <QString>
#include <QPixmap>
#include <QPlainTextEdit.h>
//#include <QSlider>
#include "lapwindow.h"


LapWindow::LapWindow(QWidget* parent) : QWidget(parent), TextArea(this), LapCounter(0)
{
    LapCounter = 0;

    BackgroundImage = QPixmap(":/icons/Ressource/chronolap.png");
    this->resize(262, 189);
    this->setWindowFlags(Qt::SubWindow | Qt::FramelessWindowHint | Qt::Tool);
    this->setAttribute(Qt::WA_TranslucentBackground);

    // Create QTextEdit (multiline text area)
    TextArea.resize(192, 91);      // Set text area size
    TextArea.move(40, 35);         // Position text area inside LapWindow
    TextArea.setReadOnly(true);
    TextArea.setStyleSheet(
        "QPlainTextEdit {"
        "   background-color: transparent;"
        "   color: white;"
        "   font-family: 'Consolas';"
        "   font-size: 13px;"
        "   font-weight: bold;"
        "   border: none;"
        "   caret-color: transparent;"
        "}"
        "QScrollBar:vertical {"
        "   background: transparent;"
        "   border: 3px solid #2D243C;"
        "   border-radius: 6px;"
        "   width: 15px;"
        "}"
        "QScrollBar::handle:vertical {"
        "   background: #6E6476;"
        "   border-radius: 6px;"
        "   min-height: 20px;"
        "}"
        "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
        "   background: transparent;"
        "   height: 0px;"
        "}"
        "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "   background: transparent;"
        "}"
        );

    TextArea.show();
}


void LapWindow::AddLapTime(QString LapTime)
{
    if(LapCounter < 1000)
    {
        TextArea.appendPlainText(QString("%1) %2").arg(LapCounter, 3, 10, QLatin1Char(' ')).arg(LapTime));
        LapCounter++;
    }
}

void LapWindow::ClearLaps()
{
    TextArea.clear();
    LapCounter = 0;
    emit HideLapWindow();
}

void LapWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, BackgroundImage); // Draw the background image
}
