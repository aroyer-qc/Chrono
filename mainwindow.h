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
#include <qmainwindow.h>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QThread>
#include "lapwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    QThread CounterThread;

  public:

    explicit MainWindow(const QString& ImagePath);
    ~MainWindow();

    const QPixmap getBackgroundImage();

protected:

    void paintEvent(QPaintEvent* Event) override;
    void mousePressEvent(QMouseEvent* Event) override;
    void mouseMoveEvent(QMouseEvent* Event) override;

  private:

    QPixmap BackgroundImage; // Private member to store the background image
    QPoint dragPosition;
    QLabel* labelStaticLCD_100_Min;
    QLabel* labelStaticLCD_10_Min;
    QLabel* labelStaticLCD_1_Min;
    QLabel* labelStaticLCD_10_Sec;
    QLabel* labelStaticLCD_1_Sec;
    QLabel* labelStaticLCD_10_HundredSEC;
    QLabel* labelStaticLCD_1_HundredSEC;
    QLabel* labelLCD_100_Min;
    QLabel* labelLCD_10_Min;
    QLabel* labelLCD_1_Min;
    QLabel* labelLCD_10_Sec;
    QLabel* labelLCD_1_Sec;
    QLabel* labelLCD_10_HundredSEC;
    QLabel* labelLCD_1_HundredSEC;
    QPushButton* buttonStart;
    QPushButton* buttonLap;
    QPushButton* buttonReset;
    int StartFlag;
    int StopFlag;

    LapWindow* LapWindow;
    bool LapWindowFlag;
    QString LapTime;

    void ResetLCD();
    void UpdateLCD(QString Data);

  private slots:

    void onButtonStartClicked();
    void onButtonLapClicked();
    void onButtonResetClicked();
    void onButtonResetLapHistoryClicked();
    void CounterFinish(QString Data);
    void HideLapWindow();

  signals:

    void StartChronometer();
    void ResetChronometer();
};


