#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	mqtt = new Mqtt();
	mqtt->set_mqtt_host("127.0.0.1");
	mqtt->set_mqtt_port(8883);
	mqtt->mqtt_connect();
	mqtt->set_mqtt_topic("mqtt/deneme");
	connect(mqtt, &Mqtt::received, this, [=](QString message){
			ui->textReceive->append(message);
		});
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::on_pushButton_clicked()
{
	mqtt->mqtt_publish(ui->textSend->toPlainText());
	ui->textSend->clear();
}

