#include <QApplication>
#include <QtGlobal>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QChar>
#include <QProcess>
#include <QMovie>
#include <QPushButton>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QObject>
#include <QTimer>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    bool ok;

    QProcess *proc = new QProcess;
    proc->start("bash", QStringList() << "-c" << "uptime | awk '{ print $8 }'");
    proc->waitForFinished(-1);

    static QString stdout = proc->readAllStandardOutput();
    stdout.truncate(stdout.lastIndexOf(QChar('.')));
    qWarning() << stdout;
    static int i = stdout.toInt(&ok);

    QWidget *window = new QWidget();
    window->resize(370,288);
    window->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    window->setAttribute(Qt::WA_TranslucentBackground);
    window->move(1800,900);

    QMediaPlayer *player = new QMediaPlayer();
    QVideoWidget *v_w = new QVideoWidget();

    player->setVideoOutput(v_w);
    player->setVolume(25);

    QHBoxLayout *hbos = new QHBoxLayout;
    hbos->addWidget(v_w);

    window->setLayout(hbos);



    static int i2;
    QTimer *timer1 = new QTimer();
    QObject::connect(timer1,&QTimer::timeout,[=](){
        proc->start("bash", QStringList() << "-c" << "uptime | awk '{ print $8 }'");
        proc->waitForFinished(-1);
        stdout = proc->readAllStandardOutput();
        stdout.truncate(stdout.lastIndexOf(QChar('.')));
        i = stdout.toInt();
        timer1->setInterval(2000);

        if(i2 != i){
            switch (i) {
            case 2:
                window->show();
                player->setMedia(QUrl::fromLocalFile("/home/ajinkya/Videos/25.mp4"));
                player->play();
                timer1->stop();
                i2 = i;
                break;
            case 4:
                window->show();
                player->setMedia(QUrl::fromLocalFile("/home/ajinkya/Videos/50.mp4"));
                player->play();
                timer1->stop();
                i2 = i;
                break;
            case 6:
                window->show();
                player->setMedia(QUrl::fromLocalFile("/home/ajinkya/Videos/75.mp4"));
                player->play();
                timer1->stop();
                i2 = i;
                break;
            case 8:
                window->show();
                player->setMedia(QUrl::fromLocalFile("/home/ajinkya/Videos/100.mp4"));
                player->play();
                timer1->stop();
                i2 = i;
                break;
        default:
            break;
        }
        }
    });

    timer1->start();
    QObject::connect(player,&QMediaPlayer::stateChanged,[=](){
        if(player->state() == 0){
            //qApp->exit(0);
            window->hide();
            timer1->start();
        }
    });

    return a.exec();
}
