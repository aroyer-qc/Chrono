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
#include <QApplication>
//#include <windows.h>
//#include <wingdi.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icons/Ressource/chrono.ico"));

    // Provide the path to the background image
    MainWindow widget(":/icons/Ressource/chrono.png");
    widget.setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    widget.resize(QSize(294, 368)); // Resize the widget with the new dimensions


    QPushButton* buttonExit = new QPushButton("X", &widget);
    QString Style = "QPushButton {"
                    "background-color: transparent;" // Makes the button transparent
                    "font-family: Arial Black;"      // Set font to Arial
                    "font-size: 14px;"               // Set font size to 20
                    "font-weight: bold;"             // Make the text bold
                    "color: black;"                  // Sets text color to white
                    "border: none;"                  // Removes any border
                    "}"
                    "QPushButton:pressed {"
                    "   color: lightgray;"           // Change text color to white when pressed
                    "}";
    buttonExit->setStyleSheet(Style);
    buttonExit->resize(24, 24);
    buttonExit->move(264, 6);
    QObject::connect(buttonExit, &QPushButton::clicked, &app, &QCoreApplication::quit);

    QLabel staticTime("Min.        Sec.    1/100", &widget);
    staticTime.move(70, 42);  // Position the label
    staticTime.setStyleSheet("color: white; font-family: Arial; font-size: 18px; font-weight: bold;");

    QString StyleSheetDot("color: white; font-family: Arial; font-size: 48px; font-weight: bold;");
    QLabel staticDot1(":", &widget);
    staticDot1.move(122, 59);  // Position the label
    staticDot1.resize(10, 48); // Resize the label if necessary
    staticDot1.setStyleSheet(StyleSheetDot);
    QLabel staticDot2(":", &widget);
    staticDot2.move(187, 59);  // Position the label
    staticDot2.resize(10, 48); // Resize the label if necessary
    staticDot2.setStyleSheet(StyleSheetDot);

    widget.show();

    return app.exec();
}
