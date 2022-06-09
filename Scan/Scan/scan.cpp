#include "scan.h"
#include "ui_scan.h"
#include<QDebug>
#include<QJsonObject>
#include<QJsonDocument>

Scan::Scan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Scan)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&Scan::postBack);//通信完成后，自动执行getBack
    //post();
    postTest();
}

Scan::~Scan()
{
    delete ui;
}

QString Scan::getTimeStamp(void)
{
    QDateTime dateTime = QDateTime::currentDateTime();
    // 字符串格式化
    QString timestamp = dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz");
    // 转换成时间戳
    qint64 epochTime = dateTime.toMSecsSinceEpoch();

    QString mstimestamp = tr("%1").arg(epochTime);

    return mstimestamp;
}

QString Scan::calcMD5(QString source)
{
    QString md5;
    QByteArray ba,bb;
    QCryptographicHash md(QCryptographicHash::Md5);

    ba.append(source);
    md.addData(ba);
    bb = md.result();
    md5.append(bb.toHex());

    return md5;
}
void Scan::postTest()
{
    qDebug() << "postTest";

// Json数据
    QJsonObject json;
    json.insert("User", "admin");
    json.insert("Password", "admin");

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

//    // 表单数据
//    QByteArray dataArray;
//    dataArray.append("username=admin&");
//    dataArray.append("password=admin");


    // 构造请求
    QNetworkRequest request;
    /*httpbin.org 这个网站能测试 HTTP 请求和响应的各种信息，比如 cookie、ip、headers 和登录验证等，且支持 GET、POST 等多种方法，对 web 开发和测试很有帮助。*/
    request.setUrl(QUrl("http://httpbin.org/post"));

    //request.setUrl(QUrl("http://10.181.218.209:8080/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // 发送请求
    manager->post(request, dataArray);
}
void Scan::post()
{
    qDebug() << "post";

    // Json数据
    QJsonObject json;

#if 0
    QString t = "1456423044000";
    QString memberID = "125725728";
    QString brandID = "1";
    QString posWebServiceKey = "WUsCxdwuP2k3wwqv";
    QString md5 = calcMD5(t  + memberID + brandID + posWebServiceKey);
    qDebug() << md5;
#endif

#if 1
    QString posWebServiceKey = "WUsCxdwuP2k3wwqv";
    QString memberID = "125725728";
    QString Phone = "0";
    QString brandID = "258";
    QString shopCode = "Sino Group	001	Sino Inno Lab";
    QString t = getTimeStamp();
    QString h = calcMD5(t + memberID + brandID + posWebServiceKey);
    QString pos = "smartmore";
    QString nonce = "1";

    json.insert("memberID", memberID);
    json.insert("Phone", Phone);
    json.insert("brandID", brandID);
    json.insert("shopCode", shopCode);
    json.insert("t", t);
    json.insert("h", h);
    json.insert("pos", pos);
    json.insert("nonce", nonce);

    qDebug() << json;

    QJsonDocument document;
    document.setObject(json);
    QByteArray dataArray = document.toJson(QJsonDocument::Compact);

#if 0
    // 表单数据
    QByteArray dataArray;
    dataArray.append("username=admin&");
    dataArray.append("password=admin");
#endif

    // 构造请求
    QNetworkRequest request;
    request.setUrl(QUrl("https://uat.storellet.com/storellet/api/pos"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 发送请求
    manager->post(request, dataArray);
#endif
}


void Scan::postBack(QNetworkReply* reply)
{
    qDebug() << "postBack";

    //qDebug()<<reply->readAll().data(); //输出所有响应内容

    // 获取响应信息
    QByteArray bytes = reply->readAll();

    QJsonParseError jsonError;
    QJsonDocument doucment = QJsonDocument::fromJson(bytes, &jsonError);
    if (jsonError.error != QJsonParseError::NoError)
    {
        qDebug() << QStringLiteral("解析Json失败");
        return;
    }

    // 解析Json
    if (doucment.isObject())
    {
        QJsonObject obj = doucment.object();
        QJsonValue value;
        if (obj.contains("data"))
        {
            value = obj.take("data");
            if (value.isString())
            {
                QString data = value.toString();
                qDebug() << data;
            }
        }
     }
}
