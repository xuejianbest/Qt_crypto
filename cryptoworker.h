#ifndef CRYPTOWORKER_H
#define CRYPTOWORKER_H

#include <QObject>
#include <QCryptographicHash>
#include <QFile>

class CryptoWorker : public QObject
{
    Q_OBJECT
public:
    explicit CryptoWorker(QObject *parent = nullptr);
    ~CryptoWorker();

signals:
    void crypto_done(const QString &res);

public slots:
    void on_crypto(const QString &content, QSet<QCryptographicHash::Algorithm> *p_methodSet);
    void on_crypto(QFile *p_file, QSet<QCryptographicHash::Algorithm> *p_methodSet);

private:
    QCryptographicHash *cryptorMd5;
    QCryptographicHash *cryptorMd4;
    QCryptographicHash *cryptorSha1;
    QCryptographicHash *cryptorSha224;
    QCryptographicHash *cryptorSha256;
    QCryptographicHash *cryptorSha384;
    QCryptographicHash *cryptorSha512;
    QCryptographicHash *cryptorSha3_224;
    QCryptographicHash *cryptorSha3_256;
    QCryptographicHash *cryptorSha3_384;
    QCryptographicHash *cryptorSha3_512;
};

#endif // CRYPTOWORKER_H
