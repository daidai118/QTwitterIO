#include "example.hpp"
#include "unistd.h"
#include <QApplication>
int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QNetworkProxyFactory::setUseSystemConfiguration(true);	
	Tweeter twi("(insert consumer_key here)", "(insert consumer_secret here)"); 
+  if (twi.initialize()){
 +    twi.Tweet("test tweet");
 +  }else{
 +    qDebug()<<"please try again after initialization";
 	return app.exec();
 +  }	
    return app.exec();
}










