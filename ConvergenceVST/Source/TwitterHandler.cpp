/*
  ==============================================================================

    TwitterHandler.cpp
    Created: 3 May 2013 11:14:39pm
    Author:  Jordan Hochenbaum & Owen Vallis

  ==============================================================================
*/

#include "TwitterHandler.h"

TwitterHandler::TwitterHandler() :connected(false), tweetUpdateInterval(1000)
{
    twitt.setup(name, pass, c_k, c_s);
    setTrendGeoLocation(NY);
    startTimer(15 * 60000);
}

TwitterHandler::~TwitterHandler() {
    
}

void TwitterHandler::init() {
    DBG("Twiter init...");
    twitterPage = 1;
    millis = Time::currentTimeMillis()+tweetUpdateInterval;
    connected = updateTrends();
}

void TwitterHandler::disconnect() {
    twitter.clear();
    topTrends.clear();
}

bool TwitterHandler::updateTrends() {
    
    //URL url("http://api.twitter.com/1/trends/" + trendWOEID + ".json");

    // Attempt to open and parse JSON URL
    //ScopedPointer<InputStream> urlStream(url.createInputStream(false));
    twitt.getTrend(trendWOEID.toStdString());
    var trendsParsed = JSON::parse(twitt.getData());
    var masterJSON = (*trendsParsed.getArray())[0];
    var trends = masterJSON.getProperty((Identifier)"trends", -1);
    DBG("number of trends");
    DBG(trends.size());
    for(int i = 0; i < trends.size(); i++)
    {
        
        topTrends.add(trends[i].getProperty((Identifier)"query", -1).toString());
        DBG(topTrends[i]);
    }
    
    if (trends.size() >0) {
        return true;
    }else{
        return false;
    }

}

void TwitterHandler::timerCallback(){
    std::cout << "trends updating..." << std::endl;
    updateTrends();
}

void TwitterHandler::updateTweets() {
    
    if(topTrends.size() > 0)
    {
        DBG("tweets updating...has trends");
        if (Time::currentTimeMillis()-millis > tweetUpdateInterval)
        {
            startTwitterPostQuery(topTrends[Random::getSystemRandom().nextInt(topTrends.size())-1], 10);
            millis = Time::currentTimeMillis();
        }
    } else {
        DBG("no trends");
    }
}

void TwitterHandler::startTwitterPostQuery(String keywords, int repliesPerPage, int pageIndex, int queryIdentifier) {
    std::cout << "starting query... " << keywords.toStdString() << std::endl;
    
    tweetQueryIdentifier = queryIdentifier;
 
    twitt.search( keywords.replace("+", "%2B").toStdString());
    DBG(keywords);
    var tweetParsed = JSON::parse(twitt.getData());
    var JSONtweets = tweetParsed.getProperty((Identifier) "statuses", -1);
        
    tweets.clear();
    DBG("number of tweets");
    DBG(JSONtweets.size());
    for (int i = 0; i < JSONtweets.size(); i++) {
        
        Tweet tweet;
        
        tweet.id = JSONtweets[i].getProperty((Identifier) "id", -1).toString();
        tweet.text = JSONtweets[i].getProperty((Identifier) "text", -1).toString();
        //DBG(tweet.text);
        tweet.created_at = JSONtweets[i].getProperty((Identifier) "created_at", -1).toString();
        tweet.author.uri = JSONtweets[i].getProperty((Identifier) "from_user_id_str", -1).toString();
        tweet.author.name = JSONtweets[i].getProperty((Identifier) "from_user_name", -1).toString();
        tweet.language = JSONtweets[i].getProperty((Identifier) "iso_language_code", -1).toString();
        tweet.author.imageUri = JSONtweets.getProperty((Identifier) "profile_image_url", -1);
    

        tweets.add(tweet);
        
    }
    
    
}

String TwitterHandler::getRandomTweet() {
    
    if (isConnected() && hasTweets())
    {
        String result = tweets[Random::getSystemRandom().nextInt(tweets.size()-1)].text;
        //DBG(result);
        return result;
    }else{
        return "empty";
    }
}

void TwitterHandler::searchResult(Array<Tweet> results, int queryType) {

    //DBG("tweets size:" + String(tweets.size()) + " results size: " + String(results.size()));
    
    for(int i = 0; i < tweets.size(); i++)
    {
        //make sure we've gotten enough results (10), otherwise temporarily
        //repeat the last returned tweet
        if(i<results.size()){
            tweets[i] = results[i];
        }else{
            tweets[i] = tweets[i-1];
        }
    }
}

void TwitterHandler::setTweetUpdateInterval(float interval){
    tweetUpdateInterval = interval*1000;
    //DBG(tweetUpdateInterval);
    millis = Time::currentTimeMillis()+tweetUpdateInterval+1;
}

void TwitterHandler::setTrendGeoLocation(int location){
    switch (location) {
            
        case Global:
            trendWOEID = "1"; break;
            
        case NY:
            trendWOEID = "2459115"; break;
            
        case Paris:
            trendWOEID = "615702" ; break;
            
        case London:
            trendWOEID = "44418"; break;
        default:
            trendWOEID = "1"; break;
    }
}
