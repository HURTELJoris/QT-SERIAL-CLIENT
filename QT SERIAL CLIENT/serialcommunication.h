#pragma once
#include <QtSerialPort/QSerialPort>
#include <QObject>
#include <QDebug>
#include <iostream>
#include <QTextStream>
#include <QThread> // Inclure la directive pour QThread

class SerialCommunication : public QObject
{
    Q_OBJECT

public:
    SerialCommunication();
    ~SerialCommunication();

    bool openSerialPort(const QString& portName);
    void closeSerialPort();
    bool writeData(const QByteArray& data);

signals:
    void dataReceived(const QByteArray& data);

private slots:
    void readData();

private:
    QSerialPort serialPort;
    QByteArray buffer;
};
void senderThread(SerialCommunication* serialComm);