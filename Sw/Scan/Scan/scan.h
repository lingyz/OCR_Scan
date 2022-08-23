#ifndef SCAN_H
#define SCAN_H

#include <QWidget>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class Scan; }
QT_END_NAMESPACE

class Scan : public QWidget
{
    Q_OBJECT

public:
    Scan(QWidget *parent = nullptr);
    ~Scan();

    QString getTimeStamp(void);
    QString calcMD5(QString source);

    void post();
    void postTest();
    void postBack(QNetworkReply* reply);

private:
    Ui::Scan *ui;
    QNetworkAccessManager * manager;
};
#endif // SCAN_H
