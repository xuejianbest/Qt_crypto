#include "widget.h"
#include "ui_widget.h"
#include <QRegExp>
#include <QDebug>
#include <QFileDialog>
#include "cryptoworker.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->rb_text->setChecked(true);
    ui->cb_Md5->click();
    CryptoWorker *cryptoWorker = new CryptoWorker();
    cryptoWorker->moveToThread(&workerThread);
    connect(&workerThread, &QThread::finished, cryptoWorker, &CryptoWorker::deleteLater);
    connect(this, static_cast<void (Widget:: *)(const QString &, QSet<QCryptographicHash::Algorithm> *)>(&Widget::crypto), cryptoWorker, static_cast<void (CryptoWorker:: *)(const QString &, QSet<QCryptographicHash::Algorithm> *)>(&CryptoWorker::on_crypto));
    connect(this, static_cast<void (Widget:: *)(QFile *, QSet<QCryptographicHash::Algorithm> *)>(&Widget::crypto), cryptoWorker, static_cast<void (CryptoWorker:: *)(QFile *, QSet<QCryptographicHash::Algorithm> *)>(&CryptoWorker::on_crypto));
    connect(cryptoWorker, &CryptoWorker::crypto_done, this, &Widget::on_cryptoDone);
    workerThread.start();
}

Widget::~Widget()
{
    delete ui;
    workerThread.quit();
    workerThread.terminate();
}

void Widget::showCryptoType(){
    QString show = ui->resBrowser->toPlainText();
    QString content = ui->lineEdit_bd->text();
    QRegExp reg(tr("([^\n]*): %1(\n|$)").arg(content), Qt::CaseInsensitive);
    if(show.indexOf(reg) >=0){
        ui->label_type->setText(reg.cap(1));
    }else{
        ui->label_type->setText("None");
    }
}

void Widget::on_calBtn_clicked() //计算按钮
{
    if(cb_checked_set.isEmpty()){
        ui->label_progress->setText(tr("请选择加密算法!"));
        return;
    }
    ui->calBtn->setEnabled(false);
    if(ui->rb_file->isChecked()){
        QFile *p_file = new QFile(ui->filenameBrowser->toPlainText());
        if(p_file->open(QIODevice::ReadOnly)){
            emit crypto(p_file, &cb_checked_set);
        }else{
            ui->label_progress->setText(tr("文件打开失败!"));
            ui->calBtn->setEnabled(true);
            return;
        }
    }else if(ui->rb_text->isChecked()){
        emit crypto(ui->plainTextEdit->toPlainText(), &cb_checked_set);
    }else{
        ui->label_progress->setText(tr("请选择加密对象!"));
    }
}

void Widget::on_cryptoDone(const QString &res){
    if(res == "start"){
        ui->resBrowser->clear();
        ui->label_progress->setText(tr("加密中..."));
    }else if(res == "done"){
        ui->label_progress->setText(tr("加密完成."));
        ui->calBtn->setEnabled(true);
    }else{
        ui->resBrowser->append(res);
    }
    showCryptoType();
}

void Widget::on_lineEdit_bd_textChanged(const QString &arg1)
{
    showCryptoType();
}

void Widget::on_plainTextEdit_textChanged()
{
    ui->rb_text->setChecked(true);
}

void Widget::on_fileSelBtn_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("打开文件："), "", "All files(*)");
    if(filename.isEmpty()){
        return;
    }
    ui->filenameBrowser->setText(filename);
    ui->rb_file->setChecked(true);
}

void Widget::on_cb_All_toggled(bool checked)
{
    ui->cb_Md5->setChecked(checked);
    ui->cb_Md4->setChecked(checked);
    ui->cb_Sha1->setChecked(checked);
    ui->cb_Sha224->setChecked(checked);
    ui->cb_Sha256->setChecked(checked);
    ui->cb_Sha384->setChecked(checked);
    ui->cb_Sha512->setChecked(checked);
    ui->cb_Sha3_224->setChecked(checked);
    ui->cb_Sha3_256->setChecked(checked);
    ui->cb_Sha3_384->setChecked(checked);
    ui->cb_Sha3_512->setChecked(checked);
    if(checked){
        cb_checked_set << QCryptographicHash::Md5;
        cb_checked_set << QCryptographicHash::Md4;
        cb_checked_set << QCryptographicHash::Sha1;
        cb_checked_set << QCryptographicHash::Sha224;
        cb_checked_set << QCryptographicHash::Sha256;
        cb_checked_set << QCryptographicHash::Sha384;
        cb_checked_set << QCryptographicHash::Sha512;
        cb_checked_set << QCryptographicHash::Sha3_224;
        cb_checked_set << QCryptographicHash::Sha3_256;
        cb_checked_set << QCryptographicHash::Sha3_384;
        cb_checked_set << QCryptographicHash::Sha3_512;
    }else{
        cb_checked_set.clear();
    }
}

void Widget::on_cb_Md5_clicked()
{
    if(ui->cb_Md5->isChecked()){
        cb_checked_set << QCryptographicHash::Md5;
    }else{
        cb_checked_set.remove(QCryptographicHash::Md5);
    }
}

void Widget::on_cb_Md4_clicked()
{
    if(ui->cb_Md4->isChecked()){
        cb_checked_set << QCryptographicHash::Md4;
    }else{
        cb_checked_set.remove(QCryptographicHash::Md4);
    }
}

void Widget::on_cb_Sha1_clicked()
{
    if(ui->cb_Sha1->isChecked()){
        cb_checked_set << QCryptographicHash::Sha1;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha1);
    }
}

void Widget::on_cb_Sha224_clicked()
{
    if(ui->cb_Sha224->isChecked()){
        cb_checked_set << QCryptographicHash::Sha224;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha224);
    }
}

void Widget::on_cb_Sha256_clicked()
{
    if(ui->cb_Sha256->isChecked()){
        cb_checked_set << QCryptographicHash::Sha256;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha256);
    }
}

void Widget::on_cb_Sha384_clicked()
{
    if(ui->cb_Sha384->isChecked()){
        cb_checked_set << QCryptographicHash::Sha384;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha384);
    }
}

void Widget::on_cb_Sha512_clicked()
{
    if(ui->cb_Sha512->isChecked()){
        cb_checked_set << QCryptographicHash::Sha512;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha512);
    }
}

void Widget::on_cb_Sha3_224_clicked()
{
    if(ui->cb_Sha3_224->isChecked()){
        cb_checked_set << QCryptographicHash::Sha3_224;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha3_224);
    }
}

void Widget::on_cb_Sha3_256_clicked()
{
    if(ui->cb_Sha3_256->isChecked()){
        cb_checked_set << QCryptographicHash::Sha3_256;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha3_256);
    }
}

void Widget::on_cb_Sha3_384_clicked()
{
    if(ui->cb_Sha3_384->isChecked()){
        cb_checked_set << QCryptographicHash::Sha3_384;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha3_384);
    }
}

void Widget::on_cb_Sha3_512_clicked()
{
    if(ui->cb_Sha3_512->isChecked()){
        cb_checked_set << QCryptographicHash::Sha3_512;
    }else{
        cb_checked_set.remove(QCryptographicHash::Sha3_512);
    }
}
