#include "example.hpp"
#include "unistd.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QNetworkProxyFactory::setUseSystemConfiguration(true);	
	Tweeter twi("(insert consumer_key here)", "(insert consumer_secret here)"); 
	twi.initialize();
	twi.Tweet("test tweet");
	
    return app.exec();
}










