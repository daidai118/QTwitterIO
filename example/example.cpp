#include "example.hpp"
#include "unistd.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QNetworkProxyFactory::setUseSystemConfiguration(true);	
	Tweeter twi("(insert consumer_key here)", "(insert consumer_secret here)"); 
	if (twi.initialize()){
		twi.Tweet("test tweet");
	}else{
		QWidget *wid=new QWidget();
		QLabel *label= new QLabel(wid);
		label->resize(300,100);
		label->setWordWrap(true);
		label->setText("Launching OAuth process. please try again after authentification. If your browser doesn't start, please check network connection.");
		wid->show();
		return app.exec();
	}

    return app.exec();
}










