#ifndef TWITTERIO_CPP
#define TWITTERIO_CPP 

#include "TwitterIO.hpp"
#include <QtNetwork/QtNetwork>
#include <QtCore/QString>
#include <QtCore/QMessageAuthenticationCode>
#include "config.hpp"

namespace QTwitterIO
{

	QString TwitterIO::formatQuery(QueryMap const& queryMap, QChar const& delimiter){
		QString str;
		QMapIterator<QString, QString> iter=queryMap;
		while(iter.hasNext()){
			iter.next();
			str+=iter.key() + "=" + iter.value() + delimiter;
		}
		str.resize(str.size()-1);
		return str;
	}

	QueryMap TwitterIO::getCommonParams(){
		QueryMap params;
		params["oauth_consumer_key"] = consumer_key;
		params["oauth_nonce"] = QString::number(rand());
		params["oauth_signature_method"] = "HMAC-SHA1";
		params["oauth_timestamp"] = QString::number(time(NULL));
		params["oauth_token"] = access_token;
		params["oauth_version"] = "1.0";
		return params;
	}

	QByteArray TwitterIO::getSignature(QString const& url,QString const& params_str, QString http_method){
		QByteArray message = http_method.toUtf8() + "&" + url.toUtf8().toPercentEncoding() + "&" + params_str.toUtf8().toPercentEncoding();
		QByteArray key = consumer_secret.toUtf8() + "&" + access_token_secret.toUtf8();
		return QMessageAuthenticationCode::hash(message, key, QCryptographicHash::Sha1).toBase64();
	}
	QByteArray const TwitterIO::getAuthorization(QueryMap& params){
		QString header_params_str= formatQuery(params, ',');
		return "OAuth "+header_params_str.toUtf8();
	}

	QueryMap TwitterIO::addSignatureParam(QString const& url, QueryMap& params, QString const& method){
		QueryMap newParams;

		addQueryMap(newParams, params);

		QString params_str= formatQuery(params, '&');
		QByteArray signature= getSignature(url, params_str, method);
		newParams["oauth_signature"] = QString::fromUtf8(signature.toPercentEncoding());
		return newParams;
	}

	void TwitterIO::addQueryMap(QueryMap& dest, QueryMap const& src){
		QueryMapIterator iter=src;
		while(iter.hasNext()){
			iter.next();
			dest.insert(iter.key(), QString::fromUtf8(iter.value().toUtf8().toPercentEncoding()));
		};
	}
	void TwitterIO::addQueryMapToUrlQuery(QUrlQuery& dest, QueryMap const& src){
		QueryMapIterator iter=src;
		while(iter.hasNext()){
			iter.next();
			dest.addQueryItem(iter.key(), QString::fromUtf8(iter.value().toUtf8().toPercentEncoding()));
		};
	}

	QNetworkReply* TwitterIO::POST_impl(QString const& url,QueryMap const& query){
		QueryMap params = getCommonParams();

		addQueryMap(params, query);

		QueryMap newParams= addSignatureParam(url, params, "POST");
		QUrl postUrl(url);
		QNetworkRequest request(postUrl);

		request.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
		request.setRawHeader( "Authorization", getAuthorization(newParams));
		QUrlQuery urlQuery;
		addQueryMapToUrlQuery(urlQuery, query);
		return post(request, urlQuery.query(QUrl::FullyEncoded).toUtf8());
	}

	QNetworkReply* TwitterIO::GET_impl(QString const& url, QueryMap const& query){

		QueryMap params=getCommonParams();
		addQueryMap(params, query);
		QString params_str= formatQuery(params, '&');
		QByteArray signature= getSignature(url, params_str, "GET");
		params.insert("oauth_signature", QString::fromUtf8(signature.toPercentEncoding()));
		QNetworkRequest req;
		QString urlStr=url;

		urlStr.append('?').append(params_str);
		QUrl newUrl(urlStr);
		req.setUrl(newUrl);
		req.setRawHeader("Authorization", getAuthorization(params));
		return get(req);
	}

	TwitterIO::TwitterIO(QString const consumer_key, QString const consumer_secret, QObject* parent)
		:QNetworkAccessManager(parent)
		,o1(new O1Twitter(this))
		,consumer_key(consumer_key)
		,consumer_secret(consumer_secret)
	{}

	bool TwitterIO::linked(){
		return o1.linked();
	}

	void TwitterIO::unlink(){
		o1.unlink();
	}

	bool TwitterIO::initialize(){

		o1.setClientId(consumer_key);
		o1.setClientSecret(consumer_secret);
		connect(&o1, &O1Twitter::linkedChanged, this, &TwitterIO::on_auth_Changed);
		connect(&o1, &O1Twitter::linkingFailed, this, &TwitterIO::on_auth_Failed);
		connect(&o1, &O1Twitter::openBrowser, this, &TwitterIO::on_auth_OpenBrowser);
		connect(&o1, &O1Twitter::closeBrowser, this, &TwitterIO::on_auth_CloseBrowser);
		connect(&o1, &O1Twitter::linkingSucceeded, this, &TwitterIO::on_auth_Finished);
		o1.link();
		return o1.linked();
	}
	QNetworkReply* TwitterIO::account_verify_credentials(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::account_verify_credentials_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::application_rate_limit_status(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::application_rate_limit_status_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::blocks_ids(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::blocks_ids_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::blocks_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::blocks_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::direct_messages(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::direct_messages_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::direct_messages_sent(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::direct_messages_sent_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::direct_messages_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::direct_messages_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::favorites_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::favorites_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::followers_ids(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::followers_ids_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::followers_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::followers_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friends_ids(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friends_ids_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friends_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friends_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_incoming(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friendships_incoming_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_lookup(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friendships_lookup_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_no_retweets_ids(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friendships_no_retweets_ids_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_outgoing(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friendships_outgoing_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::friendships_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::geo(long geo, QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::geo_id_url.arg(geo) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::geo_reverse_geocode(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::geo_reverse_geocode_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::geo_search(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::geo_search_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::geo_similar_places(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::geo_similar_places_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::help_configuration(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::help_configuration_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::help_languages(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::help_languages_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::help_privacy(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::help_privacy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::help_tos(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::help_tos_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_members_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_members_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_memberships(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_memberships_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_ownerships(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_ownerships_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_statuses(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_statuses_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_subscribers(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_subscribers_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_subscribers_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::lists_subscribers_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth_authenticate(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::oauth_authenticate_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth_authorize(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::oauth_authorize_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::saved_searches_list(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::saved_searches_list_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::saved_searches_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::saved_searches_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::search_tweets(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::search_tweets_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::site(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::site_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_firehose(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_firehose_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_home_timeline(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_home_timeline_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_mentions_timeline(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_mentions_timeline_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_oembed(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_oembed_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_retweeters_ids(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_retweeters_ids_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_retweets(long id, QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_retweets_url.arg(id) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_retweets_of_me(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_retweets_of_me_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_sample(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_sample_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_show(long id, QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_show_url.arg(id) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_user_timeline(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::statuses_user_timeline_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::trends_available(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::trends_available_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::trends_closest(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::trends_closest_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::trends_place(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::trends_place_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::user(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::user_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_contributees(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_contributees_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_contributors(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_contributors_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_lookup(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_lookup_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_profile_banner(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_profile_banner_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_search(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_search_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_show(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_show_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_suggestions(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_suggestions_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_suggestions(QString const slug, QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_suggestions_slug_url.arg(slug) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_suggestions_slug_members(QString const slug, QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::users_suggestions_slug_members_url.arg(slug) + config::url_suffix, query);
	}

	QNetworkReply* TwitterIO::account_remove_profile_banner(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_remove_profile_banner_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::post_account_settings(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_settings_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::get_account_settings(QueryMap const& query){
		return GET_impl(config::api_twitter_com + config::account_settings_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_delivery_device(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_delivery_device_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_profile(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_profile_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_profile_background_image(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_profile_background_image_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_profile_banner(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_profile_banner_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_profile_colors(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_profile_colors_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::account_update_profile_image(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::account_update_profile_image_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::blocks_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::blocks_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::blocks_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::blocks_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::direct_messages_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::direct_messages_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::direct_messages_new(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::direct_messages_new_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::favorites_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::favorites_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::favorites_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::favorites_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::friendships_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::friendships_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::friendships_update(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::friendships_update_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::geo_place(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::geo_place_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_members_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members_create_all(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_members_create_all_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_members_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_members_destroy_all(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_members_destroy_all_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_subscribers_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_subscribers_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_subscribers_destroy(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_subscribers_destroy_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::lists_update(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::lists_update_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth_access_token(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::oauth_access_token_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth_request_token(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::oauth_request_token_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth2_invalidate_token(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::oauth2_invalidate_token_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::oauth2_token(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::oauth2_token_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::saved_searches_create(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::saved_searches_create_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::saved_searches_destroy(long id, QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::saved_searches_destroy_url.arg(id) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_destroy(long id, QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::statuses_destroy_url.arg(id) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_filter(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::statuses_filter_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_retweet(long id, QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::statuses_retweet_url.arg(id) + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_update(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::statuses_update_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::statuses_update_with_media(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::statuses_update_with_media_url + config::url_suffix, query); 
	}

	QNetworkReply* TwitterIO::users_report_spam(QueryMap const& query){
		return POST_impl(config::api_twitter_com + config::users_report_spam_url + config::url_suffix, query); 
	}

}

#endif
