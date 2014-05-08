/*
  ==============================================================================

    TwitterHandler.h
    Created: 3 May 2013 11:14:39pm
    Author:  Jordan Hochenbaum & Owen Vallis

  ==============================================================================
*/

#ifndef __TWITTERHANDLER_H_695BF105__
#define __TWITTERHANDLER_H_695BF105__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Tweet.h"
#include "FlipmuTwitcurl.h"

class TwitterHandler : public Timer{
    
public:
    
    TwitterHandler();
    ~TwitterHandler();
    
    /* called to init and setup twitter feeds */
    void init();
    
    /* called to disconnect from the Twitter service */
    void disconnect();
    
    /* update trends */
    bool updateTrends();
    
    /*update twees */
    void updateTweets();
    
    /* Returns TRUE if trends have been retrieved and parsed */
    bool hasTweets() {return (tweets.size() > 0);}
    
    /* callback function receiving vector of retrieved tweets */
    void searchResult(Array<Tweet> results, int queryType);
    
    /* returns true is connected to twitter for polling trends */
    bool isConnected(){return connected;}
    
    /* called to set the tweet update rate */
    void setTweetUpdateInterval(float interval);
    
    /* set the geo location for trending topics */
    void setTrendGeoLocation(int location);
    
    /* return a random tweet from the currently stored collection of tweets */
    String getRandomTweet();
    
    enum GeoLocation{
        Global = 0,
        NY,
        Paris,
        London,
        Mexico
    };
    
    void timerCallback();
    
    FlipmuTwitcurl twitt;
    
private:
    
    /* UI */
    bool connected;                             // communication status with twitter
    
    /* Twitter Trending topics retrievel */
    Array <String>  topTrends, twitter;         // store current top trends
    String          trendWOEID;                 // current location to retrieve trending topics from using Where On Earth ID (WOEID)
    
    void startTwitterPostQuery(String keywords,
                               int repliesPerPage = 10,
                               int pageIndex = 1,
                               int queryIdentifier =0);
    
    /* Twitter Tweet retrievel */
    int             tweetQueryIdentifier;
	int             twitterPage;                // how many pages of tweets to store
	int             millis;                     // counter
    int             tweetUpdateInterval;        // rate at which to update tweets
	Array <Tweet>   tweets;                     // current tweets retrieved
    
    std::string name = "jnatanh";
    std::string pass = "ros1n3rosine";
    std::string c_k = "OE1zmCWhbTM2r6DmnDR5G6ytE";
    std::string c_s = "hwUmYtAZMr123HNPfLYn1eYyUli13dbDpk2CkEiuA5ALYIYL9p";
    
};

#endif  // __TWITTERHANDLER_H_695BF105__
