#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include <QThread>

class MainWindow : public QWidget
{
    Q_OBJECT
    QThread CounterThread;

  public:

    MainWindow(const QString& imagePath);
    ~MainWindow();

    const QPixmap getBackgroundImage();

  protected:

    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

  private:

    QPixmap backgroundImage; // Private member to store the background image
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
    int LapCounter;
    QString LapTime;


    void ResetLCD();
    void UpdateLCD(QString Data);

  private slots:

    void onButtonStartClicked();
    void onButtonLapClicked();
    void onButtonResetClicked();
    void CounterFinish(QString data);

  signals:

    void StartChronometer();
    void ResetChronometer();


};


