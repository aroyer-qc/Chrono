#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QPlainTextEdit.h>

class LapWindow : public QWidget
{
    Q_OBJECT

    public:
        explicit LapWindow(QWidget* parent = nullptr);
        void AddLapTime(QString LapTime);
        void ClearLaps();

    protected:

        void paintEvent(QPaintEvent* event) override;

    private:

        QPixmap BackgroundImage;
        QPlainTextEdit TextArea;
        int LapCounter;

    signals:

        void HideLapWindow();
};
