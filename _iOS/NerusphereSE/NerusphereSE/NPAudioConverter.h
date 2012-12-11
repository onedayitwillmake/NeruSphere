//
//  NPAudioConverter.h
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/11/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MediaPlayer.h>
/**
 * NPAudioConverter uses AVReader and AVWriter to parse a song form the users iPod library
 * It maintains a mapping NSDictionary of MPMediaItem's unique keys to converted paths
 */
@interface NPAudioConverter : NSObject {
	NSMutableDictionary* _songKeyToPath;
	NSString*	_lastFileWritten;
}
@property(nonatomic, readonly) NSString* lastFileWritten;

#pragma mark Methods

// Singleton instance
+(NPAudioConverter*)sharedConverter;

// Converts a song and stores it in the documents directory, returns a string with the new path
-(NSString*)getConvertedSongPath:(MPMediaItem*)song;

// Informs of error
-(BOOL)checkError:(NSError*)error;
@end
