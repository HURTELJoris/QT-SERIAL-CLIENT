#include "serialcommunication.h"

SerialCommunication::SerialCommunication()
{
    connect(&serialPort, &QSerialPort::readyRead, this, &SerialCommunication::readData);
}

SerialCommunication::~SerialCommunication()
{
    closeSerialPort();
}

bool SerialCommunication::openSerialPort(const QString& portName)
{
    serialPort.setPortName(portName);
    serialPort.setBaudRate(QSerialPort::Baud9600);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);

    if (serialPort.open(QIODevice::ReadWrite)) {
        return true;
    }
    return false;
}

void SerialCommunication::closeSerialPort()
{
    if (serialPort.isOpen()) {
        serialPort.close();
    }
}

bool SerialCommunication::writeData(const QByteArray& data)
{
    if (serialPort.isOpen()) {
        return serialPort.write(data) != -1;
    }
    return false;
}

void SerialCommunication::readData()
{
    buffer.append(serialPort.readAll());
    emit dataReceived(buffer);
    buffer.clear();
    writeData("Message bien reçu bg");
}



void senderThread(SerialCommunication* serialComm) {
    QTextStream textStream(stdin);

    while (true) {
        qDebug() << "Envoyez un message (ou tapez 'exit' pour quitter) : ";
        QString input = textStream.readLine();
        
        

        if (input == "exit") {
            break;
        }

        serialComm->writeData(input.toUtf8());
        break;
    }
}