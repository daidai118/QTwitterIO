#include "config.hpp"

namespace QTwitterIO
{
	namespace config
	{
		QString const api_twitter_com= "https://api.twitter.com/1.1/";
		QString const url_suffix=".json";

		QString const statuses_mentions_timeline_url = "statuses/mentions_timeline";
		QString const statuses_user_timeline_url = "statuses/user_timeline";
		QString const statuses_home_timeline_url = "statuses/home_timeline";
		QString const statuses_retweets_of_me_url = "statuses/retweets_of_me";
		QString const statuses_retweets_url = "statuses/retweets/%1";
		QString const statuses_show_url = "statuses/show/%1";
		QString const statuses_destroy_url = "statuses/destroy/%1";
		QString const statuses_update_url = "statuses/update";
		QString const statuses_retweet_url = "statuses/retweet/%1";
		QString const statuses_update_with_media_url = "statuses/update_with_media";
		QString const statuses_oembed_url = "statuses/oembed";
		QString const statuses_retweeters_ids_url = "statuses/retweeters/ids";
		QString const search_tweets_url = "search/tweets";
		QString const statuses_filter_url = "statuses/filter";
		QString const statuses_sample_url = "statuses/sample";
		QString const statuses_firehose_url = "statuses/firehose";
		QString const user_url = "user";
		QString const site_url = "site";
		QString const direct_messages_url = "direct_messages";
		QString const direct_messages_sent_url = "direct_messages/sent";
		QString const direct_messages_show_url = "direct_messages/show";
		QString const direct_messages_destroy_url = "direct_messages/destroy";
		QString const direct_messages_new_url = "direct_messages/new";
		QString const friendships_no_retweets_ids_url = "friendships/no_retweets/ids";
		QString const friends_ids_url = "friends/ids";
		QString const followers_ids_url = "followers/ids";
		QString const friendships_lookup_url = "friendships/lookup";
		QString const friendships_incoming_url = "friendships/incoming";
		QString const friendships_outgoing_url = "friendships/outgoing";
		QString const friendships_create_url = "friendships/create";
		QString const friendships_destroy_url = "friendships/destroy";
		QString const friendships_update_url = "friendships/update";
		QString const friendships_show_url = "friendships/show";
		QString const friends_list_url = "friends/list";
		QString const followers_list_url = "followers/list";
		QString const account_settings_url = "account/settings";
		QString const account_verify_credentials_url = "account/verify_credentials";
		QString const account_update_delivery_device_url = "account/update_delivery_device";
		QString const account_update_profile_url = "account/update_profile";
		QString const account_update_profile_background_image_url = "account/update_profile_background_image";
		QString const account_update_profile_colors_url = "account/update_profile_colors";
		QString const account_update_profile_image_url = "account/update_profile_image";
		QString const blocks_list_url = "blocks/list";
		QString const blocks_ids_url = "blocks/ids";
		QString const blocks_create_url = "blocks/create";
		QString const blocks_destroy_url = "blocks/destroy";
		QString const users_lookup_url = "users/lookup";
		QString const users_show_url = "users/show";
		QString const users_search_url = "users/search";
		QString const users_contributees_url = "users/contributees";
		QString const users_contributors_url = "users/contributors";
		QString const account_remove_profile_banner_url = "account/remove_profile_banner";
		QString const account_update_profile_banner_url = "account/update_profile_banner";
		QString const users_profile_banner_url = "users/profile_banner";
		QString const users_suggestions_slug_url = "users/suggestions/%1";
		QString const users_suggestions_url = "users/suggestions";
		QString const users_suggestions_slug_members_url = "users/suggestions/%1/members";
		QString const favorites_list_url = "favorites/list";
		QString const favorites_destroy_url = "favorites/destroy";
		QString const favorites_create_url = "favorites/create";


		QString const lists_list_url = "lists/list";
		QString const lists_statuses_url = "lists/statuses";
		QString const lists_members_destroy_url = "lists/members/destroy";
		QString const lists_memberships_url = "lists/memberships";
		QString const lists_subscribers_url = "lists/subscribers";
		QString const lists_subscribers_create_url = "lists/subscribers/create";
		QString const lists_subscribers_show_url = "lists/subscribers/show";
		QString const lists_subscribers_destroy_url = "lists/subscribers/destroy";
		QString const lists_members_create_all_url = "lists/members/create_all";
		QString const lists_members_show_url = "lists/members/show";
		QString const lists_members_url = "lists/members";
		QString const lists_members_create_url = "lists/members/create";
		QString const lists_destroy_url = "lists/destroy";
		QString const lists_update_url = "lists/update";
		QString const lists_create_url = "lists/create";
		QString const lists_show_url = "lists/show";
		QString const lists_subscriptions_url = "lists/subscriptions";
		QString const lists_members_destroy_all_url = "lists/members/destroy_all";
		QString const lists_ownerships_url = "lists/ownerships";
		QString const saved_searches_list_url = "saved_searches/list";
		QString const saved_searches_show_url = "saved_searches/show";
		QString const saved_searches_create_url = "saved_searches/create";
		QString const saved_searches_destroy_url = "saved_searches/destroy%1";
		QString const geo_id_url = "geo/id/%1";
		QString const geo_reverse_geocode_url = "geo/reverse_geocode";
		QString const geo_search_url = "geo/search";
		QString const geo_similar_places_url = "geo/similar_places";
		QString const geo_place_url = "geo/place";

		QString const application_rate_limit_status_url = "application/rate_limit_status";
		QString const help_configuration_url = "help/configuration";
		QString const help_languages_url = "help/languages";
		QString const help_privacy_url = "help/privacy";
		QString const help_tos_url = "help/tos";
		QString const oauth_authenticate_url = "oauth/authenticate";
		QString const oauth_authorize_url = "oauth/authorize";
		QString const trends_available_url = "trends/available";
		QString const trends_closest_url = "trends/closest";
		QString const trends_place_url = "trends/place";
		QString const oauth_access_token_url = "oauth/access_token";
		QString const oauth_request_token_url = "oauth/request_token";
		QString const oauth2_invalidate_token_url = "oauth2/invalidate_token";
		QString const oauth2_token_url = "oauth2/token";
		QString const users_report_spam_url = "users/report_spam";

	}
}
