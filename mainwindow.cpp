#include "mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include <QLabel>
#include "counter.h"

MainWindow::MainWindow(const QString& imagePath)
{
    StartFlag = 0;
    LapCounter = 0;

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

    // Load the background image
    backgroundImage = QPixmap(imagePath);

    // Set the mask to match the shape of the image (for irregular shapes)
    setMask(backgroundImage.mask());

    // Create button
    buttonStart = new QPushButton(" Start", this);
    buttonLap = new QPushButton(" Lap ", this);
    buttonReset = new QPushButton("Reset", this);

    // Set the icon for the button
    buttonStart->setIcon(QIcon(":/icons/Ressource/start.png"));
    buttonLap->setIcon(QIcon(":/icons/Ressource/lap.png"));
    buttonReset->setIcon(QIcon(":/icons/Ressource/reset.png"));

    // Set the button's styles
    QString Style = "QPushButton {"
                    "background-color: transparent;" // Makes the button transparent
                    "color: white;"                  // Sets text color to white
                    "border: none;"                  // Removes any border
                    "}"
                    "QPushButton:pressed {"
                    "   color: lightgray;"           // Change text color to white when pressed
                    "}";
    buttonStart->setStyleSheet(Style);
    buttonLap->setStyleSheet(Style);
    buttonReset->setStyleSheet(Style);

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


    QString StyleSheet("font-family: 'DS-Digital'; font-size: 48px; font-weight: bold; color: #202020;");

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

    StyleSheet = ("background-color: transparent; font-family: 'DS-Digital'; font-size: 48px; font-weight: bold; color: white;");

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
}

MainWindow::~MainWindow()
{
    CounterThread.quit();
    CounterThread.wait();
}

// Public method to get background image
const QPixmap MainWindow::getBackgroundImage()
{
    return backgroundImage;
}

void MainWindow::ResetLCD()
{
    UpdateLCD("  0:00:00");
}

void MainWindow::UpdateLCD(QString data)
{
    // this function fix bad offset into the DS_Digital Font for number 1
    labelLCD_100_Min->move(data.at(0) == '1' ? 60 : 48, 62);
    labelLCD_10_Min->move(data.at(1) == '1' ? 85 : 73, 62);
    labelLCD_1_Min->move(data.at(2) == '1' ? 110 : 98, 62);
    labelLCD_10_Sec->move(data.at(4) == '1' ? 150 : 138, 62);
    labelLCD_1_Sec->move(data.at(5) == '1' ? 175 : 163, 62);
    labelLCD_10_HundredSEC->move(data.at(7) == '1' ? 215 : 203, 62);
    labelLCD_1_HundredSEC->move(data.at(8) == '1' ? 240 : 228, 62);

    labelLCD_100_Min->setText(data.at(0));
    labelLCD_10_Min->setText(data.at(1));
    labelLCD_1_Min->setText(data.at(2));
    labelLCD_10_Sec->setText(data.at(4));
    labelLCD_1_Sec->setText(data.at(5));
    labelLCD_10_HundredSEC->setText(data.at(7));
    labelLCD_1_HundredSEC->setText(data.at(8));

    if(StartFlag == 1) emit StartChronometer();
    LapTime = data;
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    // Draw the background image
    painter.drawPixmap(0, 0, backgroundImage);
}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    // Allow dragging the window by clicking anywhere
    if(event->button() == Qt::LeftButton)
    {
        dragPosition = (event->globalPosition().toPoint() - frameGeometry().topLeft());
        event->accept();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    // Handle dragging the window
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPosition().toPoint() - dragPosition);
        event->accept();
    }
}

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
        StartFlag = 0;
        StopFlag = 0;
    }

    //QIcon darkIcon("C:/path_to_darkened_icon.png"); // Use a darker version of the icon
    //button.setIcon(darkIcon);


}

void MainWindow::onButtonLapClicked()
{
    // Action performed when the button is clicked
    qDebug("Button lap clicked!");

    //QIcon darkIcon("C:/path_to_darkened_icon.png"); // Use a darker version of the icon
    //button.setIcon(darkIcon);


}

void MainWindow::onButtonResetClicked()
{
    ResetLCD();
    emit ResetChronometer();


    //QIcon darkIcon("C:/path_to_darkened_icon.png"); // Use a darker version of the icon
    //button.setIcon(darkIcon);


}

void MainWindow::CounterFinish(QString data)
{
    UpdateLCD(data);

    if(StartFlag == 1)
    {
        emit StartChronometer();
    }

   // LapTime = data;
}


/* exmaple to darken icon
QObject::connect(&button, &QPushButton::released, [&]()
{
    button.setIcon(icon); // Restore original icon
});
*/






// to animated the child window

# if 0

#include <QApplication>
#include <QWidget>
#include <QPropertyAnimation>
#include <QPushButton>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget parentWindow;
    parentWindow.resize(400, 300);
    parentWindow.setWindowTitle("Parent Window");

    QWidget childWindow(&parentWindow);
    childWindow.resize(200, 150);
    childWindow.setWindowTitle("Child Window");

    // Initially place the child window behind the parent
    childWindow.move(-200, 75); // Off-screen position

    QPushButton button("Animate Child", &parentWindow);
    button.move(150, 250);

    QObject::connect(&button, &QPushButton::clicked, [&]() {
        // Set up the animation
        QPropertyAnimation* animation = new QPropertyAnimation(&childWindow, "geometry");
        animation->setDuration(1000); // Animation duration in milliseconds
        animation->setStartValue(childWindow.geometry()); // Starting position
        animation->setEndValue(QRect(100, 75, 200, 150)); // Ending position (on-screen)
        animation->start();
    });

    parentWindow.show();

    return app.exec();
}

#endif
