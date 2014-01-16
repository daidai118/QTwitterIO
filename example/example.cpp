#include "example.hpp"
#include "unistd.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QNetworkProxyFactory::setUseSystemConfiguration(true);	
	Tweeter twi("GJ7R9EHc14oS9cM252k96Q", "e1qOvBTHCMpN32wbIdW4QNOmXUeSiEupf17h4do"); 
	if (twi.initialize()){
		twi.Tweet("test tweet");
	}else{
		qDebug()<<"please try again after initialization";
	}


    return app.exec();
}










