#include "cryptoworker.h"
#include <QByteArray>
#include <QDebug>

CryptoWorker::CryptoWorker(QObject *parent) : QObject(parent){
    cryptorMd5 = new QCryptographicHash(QCryptographicHash::Md5);
    cryptorMd4 = new QCryptographicHash(QCryptographicHash::Md4);
    cryptorSha1 = new QCryptographicHash(QCryptographicHash::Sha1);
    cryptorSha224 = new QCryptographicHash(QCryptographicHash::Sha224);
    cryptorSha256 = new QCryptographicHash(QCryptographicHash::Sha256);
    cryptorSha384 = new QCryptographicHash(QCryptographicHash::Sha384);
    cryptorSha512 = new QCryptographicHash(QCryptographicHash::Sha512);
    cryptorSha3_224 = new QCryptographicHash(QCryptographicHash::Sha3_224);
    cryptorSha3_256 = new QCryptographicHash(QCryptographicHash::Sha3_256);
    cryptorSha3_384 = new QCryptographicHash(QCryptographicHash::Sha3_384);
    cryptorSha3_512 = new QCryptographicHash(QCryptographicHash::Sha3_512);
}
CryptoWorker::~CryptoWorker(){
    delete cryptorMd5;
    delete cryptorMd4;
    delete cryptorSha1;
    delete cryptorSha224;
    delete cryptorSha256;
    delete cryptorSha384;
    delete cryptorSha512;
    delete cryptorSha3_224;
    delete cryptorSha3_256;
    delete cryptorSha3_384;
    delete cryptorSha3_512;
}

void CryptoWorker::on_crypto(QFile *p_file, QSet<QCryptographicHash::Algorithm> *p_methodSet){
    emit crypto_done("start");
    QCryptographicHash *cryptor=nullptr;
    for(QCryptographicHash::Algorithm method : *p_methodSet){
        QString res;
        switch (method) {
        case QCryptographicHash::Md5:
            cryptor = cryptorMd5;
            res += "Md5: ";
            break;
        case QCryptographicHash::Md4:
            cryptor = cryptorMd4;
            res += "Md4: ";
            break;
        case QCryptographicHash::Sha1:
            cryptor = cryptorSha1;
            res += "Sha1: ";
            break;
        case QCryptographicHash::Sha224:
            cryptor = cryptorSha224;
            res += "Sha224: ";
            break;
        case QCryptographicHash::Sha256:
            cryptor = cryptorSha256;
            res += "Sha256: ";
            break;
        case QCryptographicHash::Sha384:
            cryptor = cryptorSha384;
            res += "Sha384: ";
            break;
        case QCryptographicHash::Sha512:
            cryptor = cryptorSha512;
            res += "Sha512: ";
            break;
        case QCryptographicHash::Sha3_224:
            cryptor = cryptorSha3_224;
            res += "Sha3_224: ";
            break;
        case QCryptographicHash::Sha3_256:
            cryptor = cryptorSha3_256;
            res += "Sha3_256: ";
            break;
        case QCryptographicHash::Sha3_384:
            cryptor = cryptorSha3_384;
            res += "Sha3_384: ";
            break;
        case QCryptographicHash::Sha3_512:
            cryptor = cryptorSha3_512;
            res += "Sha3_512: ";
            break;
        }
        p_file->reset();
        cryptor->reset();
        cryptor->addData(p_file);
        res += cryptor->result().toHex();
        emit crypto_done(res);
    }
    p_file->close();
    emit crypto_done("done");
}

void CryptoWorker::on_crypto(const QString &content, QSet<QCryptographicHash::Algorithm> *p_methodSet){
    emit crypto_done("start");
    QByteArray data = content.toUtf8();
    for(QCryptographicHash::Algorithm method : *p_methodSet){
        QCryptographicHash *cryptor=nullptr;
        QString res;
        switch (method) {
        case QCryptographicHash::Md5:
            cryptor = cryptorMd5;
            res += "Md5: ";
            break;
        case QCryptographicHash::Md4:
            cryptor = cryptorMd4;
            res += "Md4: ";
            break;
        case QCryptographicHash::Sha1:
            cryptor = cryptorSha1;
            res += "Sha1: ";
            break;
        case QCryptographicHash::Sha224:
            cryptor = cryptorSha224;
            res += "Sha224: ";
            break;
        case QCryptographicHash::Sha256:
            cryptor = cryptorSha256;
            res += "Sha256: ";
            break;
        case QCryptographicHash::Sha384:
            cryptor = cryptorSha384;
            res += "Sha384: ";
            break;
        case QCryptographicHash::Sha512:
            cryptor = cryptorSha512;
            res += "Sha512: ";
            break;
        case QCryptographicHash::Sha3_224:
            cryptor = cryptorSha3_224;
            res += "Sha3_224: ";
            break;
        case QCryptographicHash::Sha3_256:
            cryptor = cryptorSha3_256;
            res += "Sha3_256: ";
            break;
        case QCryptographicHash::Sha3_384:
            cryptor = cryptorSha3_384;
            res += "Sha3_384: ";
            break;
        case QCryptographicHash::Sha3_512:
            cryptor = cryptorSha3_512;
            res += "Sha3_512: ";
            break;
        }
        cryptor->reset();
        cryptor->addData(data);
        res += cryptor->result().toHex();
        emit crypto_done(res);
    }
    emit crypto_done("done");
}
