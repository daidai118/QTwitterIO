#include "../src/TwitterIO.hpp"
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtWidgets/QtWidgets>
class Tweeter:public QObject{
	Q_OBJECT
	QTwitterIO::TwitterIO twitterIO;
	Tweeter(QObject* parent=0)=delete;
public slots:
	void on_auth_Changed(){
		qDebug()<<"Authentification condition changed.";
	}
	void on_auth_Failed(){
		qDebug()<<"Authentification failed. Please check network access.";
	}
	void on_auth_Finished(){
		qDebug()<<"Authentification finished";
	}
	void on_auth_OpenBrowser(QUrl const& url){
		QDesktopServices::openUrl(url);
	};
	void on_auth_CloseBrowser(){
		qDebug()<<"Browser closed";
	}
	void finished(){
		qDebug()<<qobject_cast<QNetworkReply*>(sender())->readAll();
	}
public:
	Tweeter(QString const& consumerKey, QString const& consumerSecret,QObject* parent=0)
		:QObject(parent)
		,twitterIO(consumerKey,consumerSecret,this)
	{};

	bool initialize(){
		connect(&twitterIO, &QTwitterIO::TwitterIO::auth_Changed, this, &Tweeter::on_auth_Changed);
		connect(&twitterIO, &QTwitterIO::TwitterIO::auth_Failed, this, &Tweeter::on_auth_Failed);
		connect(&twitterIO, &QTwitterIO::TwitterIO::auth_OpenBrowser, this, &Tweeter::on_auth_OpenBrowser);
		connect(&twitterIO, &QTwitterIO::TwitterIO::auth_Finished, this, &Tweeter::on_auth_Finished);
		connect(&twitterIO, &QTwitterIO::TwitterIO::auth_CloseBrowser, this, &Tweeter::on_auth_CloseBrowser);
		return twitterIO.initialize();
	}
	void Tweet(QString const& tweet){
		QTwitterIO::QueryMap query;
		query.insert("status", tweet);
		QNetworkReply *reply = twitterIO.statuses_update(query);
		connect(reply, &QNetworkReply::finished, this, &Tweeter::finished);
	}
};
