#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QString>
#include <QtGlobal>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_matchCheckBox_toggled(bool checked)
{

}

void MainWindow::on_findPushButton_pressed()
{
    QString file_input = ui->fileLineEdit->text();
    QString key = ui->keyLineEdit->text();
    qDebug(qUtf8Printable(file_input));
    qDebug(qUtf8Printable(key));
    QFile file(file_input);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            ui->textBrowser->setText("File not found");
            return;
        }else if(key.isEmpty()){
            ui->textBrowser->setText("File found");
            return;
        }else{
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.contains(key)){
                    ui->textBrowser->setText("Word found");
                    return;
                }
            }
            ui->textBrowser->setText("Word not found");
            return;
        }

}

