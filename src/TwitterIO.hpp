
#ifndef TWITTERIO_HPP
#define TWITTERIO_HPP

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtNetwork/QtNetwork>
#include "o2/src/o1twitter.h"
#include <QtGui/QDesktopServices>
#include <QtCore/QEventLoop>
namespace QTwitterIO
{

	typedef QMap<QString, QString> QueryMap;
	typedef QMapIterator<QString, QString> QueryMapIterator;

	class TwitterIO:public QNetworkAccessManager
	{
		Q_OBJECT
		QScopedPointer<O1Twitter> o1;
		QString const consumer_key;
		QString const consumer_secret;
		QString access_token;
		QString access_token_secret;

		QString formatQuery(QueryMap const& queryMap, QChar const& delimiter);
		QueryMap getCommonParams();
		QByteArray getSignature(QString const& url,QString const& params_str, QString http_method);
		QueryMap addSignatureParam(QString const& url, QueryMap& params, QString const& method);
		QByteArray const getAuthorization(QueryMap& params);
		void addQueryMap(QueryMap& dest, QueryMap const& src);
		void addQueryMapToUrlQuery(QUrlQuery& dest, QueryMap const& src);
		QNetworkReply* POST_impl(QString const& url,QueryMap const& query);
		QNetworkReply* GET_impl(QString const& url, QueryMap const& query);

		TwitterIO(QObject *parent=0)=delete;

		void on_auth_Changed(){
			emit auth_Changed();
		}
		void on_auth_Failed(){
			emit auth_Failed();
		}
		void on_auth_Finished(){
			access_token= o1->token();
			access_token_secret= o1->tokenSecret();
			emit auth_Finished();
		}
		void on_auth_OpenBrowser(QUrl const& url){
			emit auth_OpenBrowser(url);
		}
		void on_auth_CloseBrowser(){
			emit auth_CloseBrowser();
		}

		
	signals:
		//signals emited on authorization
		void auth_Changed();
		void auth_Failed();
		void auth_Finished();
		void auth_OpenBrowser(QUrl const& url);
		void auth_CloseBrowser();
	
	public:
		TwitterIO(QString const consumer_key, QString const consumer_secret, QObject* parent=0);

		//do oauth and return condition. You have to call it before using API functions
		bool initialize();
		
		//unlink twitter account
		void unlink();

		//return true if linked to twitter account
		bool linked();

		//APIs
		QNetworkReply* account_verify_credentials(QueryMap const& query);
		QNetworkReply* application_rate_limit_status(QueryMap const& query);
		QNetworkReply* blocks_ids(QueryMap const& query);
		QNetworkReply* blocks_list(QueryMap const& query);
		QNetworkReply* direct_messages(QueryMap const& query);
		QNetworkReply* direct_messages_sent(QueryMap const& query);
		QNetworkReply* direct_messages_show(QueryMap const& query);
		QNetworkReply* favorites_list(QueryMap const& query);
		QNetworkReply* followers_ids(QueryMap const& query);
		QNetworkReply* followers_list(QueryMap const& query);
		QNetworkReply* friends_ids(QueryMap const& query);
		QNetworkReply* friends_list(QueryMap const& query);
		QNetworkReply* friendships_incoming(QueryMap const& query);
		QNetworkReply* friendships_lookup(QueryMap const& query);
		QNetworkReply* friendships_no_retweets_ids(QueryMap const& query);
		QNetworkReply* friendships_outgoing(QueryMap const& query);
		QNetworkReply* friendships_show(QueryMap const& query);
		QNetworkReply* geo(long geo, QueryMap const& query);
		QNetworkReply* geo_reverse_geocode(QueryMap const& query);
		QNetworkReply* geo_search(QueryMap const& query);
		QNetworkReply* geo_similar_places(QueryMap const& query);
		QNetworkReply* help_configuration(QueryMap const& query);
		QNetworkReply* help_languages(QueryMap const& query);
		QNetworkReply* help_privacy(QueryMap const& query);
		QNetworkReply* help_tos(QueryMap const& query);
		QNetworkReply* lists_list(QueryMap const& query);
		QNetworkReply* lists_members(QueryMap const& query);
		QNetworkReply* lists_members_show(QueryMap const& query);
		QNetworkReply* lists_memberships(QueryMap const& query);
		QNetworkReply* lists_ownerships(QueryMap const& query);
		QNetworkReply* lists_show(QueryMap const& query);
		QNetworkReply* lists_statuses(QueryMap const& query);
		QNetworkReply* lists_subscribers(QueryMap const& query);
		QNetworkReply* lists_subscribers_show(QueryMap const& query);
		QNetworkReply* oauth_authenticate(QueryMap const& query);
		QNetworkReply* oauth_authorize(QueryMap const& query);
		QNetworkReply* saved_searches_list(QueryMap const& query);
		QNetworkReply* saved_searches_show(QueryMap const& query);
		QNetworkReply* search_tweets(QueryMap const& query);
		QNetworkReply* site(QueryMap const& query);
		QNetworkReply* statuses_firehose(QueryMap const& query);
		QNetworkReply* statuses_home_timeline(QueryMap const& query);
		QNetworkReply* statuses_mentions_timeline(QueryMap const& query);
		QNetworkReply* statuses_oembed(QueryMap const& query);
		QNetworkReply* statuses_retweeters_ids(QueryMap const& query);
		QNetworkReply* statuses_retweets(long id, QueryMap const& query);
		QNetworkReply* statuses_retweets_of_me(QueryMap const& query);
		QNetworkReply* statuses_sample(QueryMap const& query);
		QNetworkReply* statuses_show(long id, QueryMap const& query);
		QNetworkReply* statuses_user_timeline(QueryMap const& query);
		QNetworkReply* trends_available(QueryMap const& query);
		QNetworkReply* trends_closest(QueryMap const& query);
		QNetworkReply* trends_place(QueryMap const& query);
		QNetworkReply* user(QueryMap const& query);
		QNetworkReply* users_contributees(QueryMap const& query);
		QNetworkReply* users_contributors(QueryMap const& query);
		QNetworkReply* users_lookup(QueryMap const& query);
		QNetworkReply* users_profile_banner(QueryMap const& query);
		QNetworkReply* users_search(QueryMap const& query);
		QNetworkReply* users_show(QueryMap const& query);
		QNetworkReply* users_suggestions(QueryMap const& query);
		QNetworkReply* users_suggestions(QString const slug, QueryMap const& query);
		QNetworkReply* users_suggestions_slug_members(QString const slug, QueryMap const& query);
		QNetworkReply* account_remove_profile_banner(QueryMap const& query);
		QNetworkReply* post_account_settings(QueryMap const& query);
		QNetworkReply* get_account_settings(QueryMap const& query);
		QNetworkReply* account_update_delivery_device(QueryMap const& query);
		QNetworkReply* account_update_profile(QueryMap const& query);
		QNetworkReply* account_update_profile_background_image(QueryMap const& query);
		QNetworkReply* account_update_profile_banner(QueryMap const& query);
		QNetworkReply* account_update_profile_colors(QueryMap const& query);
		QNetworkReply* account_update_profile_image(QueryMap const& query);
		QNetworkReply* blocks_create(QueryMap const& query);
		QNetworkReply* blocks_destroy(QueryMap const& query);
		QNetworkReply* direct_messages_destroy(QueryMap const& query);
		QNetworkReply* direct_messages_new(QueryMap const& query);
		QNetworkReply* favorites_create(QueryMap const& query);
		QNetworkReply* favorites_destroy(QueryMap const& query);
		QNetworkReply* friendships_create(QueryMap const& query);
		QNetworkReply* friendships_destroy(QueryMap const& query);
		QNetworkReply* friendships_update(QueryMap const& query);
		QNetworkReply* geo_place(QueryMap const& query);
		QNetworkReply* lists_create(QueryMap const& query);
		QNetworkReply* lists_destroy(QueryMap const& query);
		QNetworkReply* lists_members_create(QueryMap const& query);
		QNetworkReply* lists_members_create_all(QueryMap const& query);
		QNetworkReply* lists_members_destroy(QueryMap const& query);
		QNetworkReply* lists_members_destroy_all(QueryMap const& query);
		QNetworkReply* lists_subscribers_create(QueryMap const& query);
		QNetworkReply* lists_subscribers_destroy(QueryMap const& query);
		QNetworkReply* lists_update(QueryMap const& query);
		QNetworkReply* oauth_access_token(QueryMap const& query);
		QNetworkReply* oauth_request_token(QueryMap const& query);
		QNetworkReply* oauth2_invalidate_token(QueryMap const& query);
		QNetworkReply* oauth2_token(QueryMap const& query);
		QNetworkReply* saved_searches_create(QueryMap const& query);
		QNetworkReply* saved_searches_destroy(long id, QueryMap const& query);
		QNetworkReply* statuses_destroy(long id, QueryMap const& query);
		QNetworkReply* statuses_filter(QueryMap const& query);
		QNetworkReply* statuses_retweet(long id, QueryMap const& query);
		QNetworkReply* statuses_update(QueryMap const& query);
		QNetworkReply* statuses_update_with_media(QueryMap const& query);
		QNetworkReply* users_report_spam(QueryMap const& query);
	};
}
#endif
