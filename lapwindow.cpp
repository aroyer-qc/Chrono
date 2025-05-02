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

void LapWindow::paintEvent(QPaintEvent* Event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, BackgroundImage); // Draw the background image
    Event->accept();
}
