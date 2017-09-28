#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include <QCryptographicHash>
#include <QSet>
#include <QFile>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void showCryptoType();

private slots:
    void on_lineEdit_bd_textChanged(const QString &arg1);
    void on_fileSelBtn_clicked();
    void on_cryptoDone(const QString &res);
    void on_plainTextEdit_textChanged();
    void on_calBtn_clicked();

    void on_cb_All_toggled(bool checked);
    void on_cb_Md5_clicked();
    void on_cb_Md4_clicked();
    void on_cb_Sha1_clicked();
    void on_cb_Sha224_clicked();
    void on_cb_Sha256_clicked();
    void on_cb_Sha384_clicked();
    void on_cb_Sha512_clicked();
    void on_cb_Sha3_224_clicked();
    void on_cb_Sha3_256_clicked();
    void on_cb_Sha3_384_clicked();
    void on_cb_Sha3_512_clicked();

signals:
    void crypto(const QString &content, QSet<QCryptographicHash::Algorithm> *p_method);
    void crypto(QFile *p_file, QSet<QCryptographicHash::Algorithm> *p_method);

private:
    Ui::Widget *ui;
    QThread workerThread;
    QSet<QCryptographicHash::Algorithm> cb_checked_set;
};

#endif // WIDGET_H
