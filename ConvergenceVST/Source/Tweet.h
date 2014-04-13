/*
  ==============================================================================

    Tweet.h
    Created: 3 May 2013 11:35:22pm
    Author:  Jordan Hochenbaum & Owen Vallis

  ==============================================================================
*/

#ifndef __TWEET_H_723533B3__
#define __TWEET_H_723533B3__

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct TweetAuthor {
	String name;
	String uri;
	String imageUri;
};

struct Tweet {
    
	String id;
	String created_at;
	String text;
	String language;
	
	TweetAuthor author;
	
	Tweet() { }
	Tweet(String defaultString)	: text(defaultString) { }
	
	String print() {
		String str;
		str += "id:" + id;
		str +=  "\ncreated_at:" +created_at;
		str +=  "\niso_language_code:" + language;
		str +=  "\nfrom_user_name:" + author.name;
		str +=  "\nfrom_user_id_str:" + author.uri;
		str +=  "\nprofile_image_url:" + author.imageUri;
		str +=  "\ntext:" + text;
		return str;
	}
	
};

#endif  // __TWEET_H_723533B3__
