//
//  NPAudioConverter.m
//  NerusphereSE
//
//  Created by Mario Gonzalez on 12/11/12.
//  Copyright (c) 2012 Mario Gonzalez. All rights reserved.
//

#import "NPAudioConverter.h"
#import <AudioToolbox/AudioToolbox.h> // for the core audio constants
#import <AVFoundation/AVFoundation.h>

@implementation NPAudioConverter
@synthesize lastFileWritten=_lastFileWritten;

+(NPAudioConverter*)sharedConverter {
	static NPAudioConverter* _sharedConverter = nil;
	static dispatch_once_t onceToken;
	dispatch_once(&onceToken, ^{
		_sharedConverter = [[self alloc] init];
	});
	return _sharedConverter;
}

- (id)init {
    self = [super init];
    if (self) {
        _songKeyToPath = [NSMutableDictionary dictionaryWithCapacity:10];
    }
    return self;
}
-(void)dealloc {
	_songKeyToPath = nil;
}


#pragma mark Methods
-(NSString*)getConvertedSongPath:(MPMediaItem*)song {
	NSURL*			assetURL = [song valueForProperty:MPMediaItemPropertyAssetURL];
	AVURLAsset*		songAsset = [AVURLAsset URLAssetWithURL:assetURL options:nil];
	
	NSError*		error;
	AVAssetReader*	assetReader = [AVAssetReader assetReaderWithAsset:songAsset error:&error];
	
	// Check for error during read
	if([self checkError:error]) return nil;
	
	// Add the reader's output 
	AVAssetReaderOutput*	assetReaderOutput = [AVAssetReaderAudioMixOutput assetReaderAudioMixOutputWithAudioTracks:songAsset.tracks audioSettings:nil];
	if( ![assetReader canAddOutput:assetReaderOutput] ) {
		NSLog(@"NPAudioConverter Error: Cannot add reader output!");
		return nil;
	}
	[assetReader addOutput: assetReaderOutput];
	
	// Get the unique path for this song
	NSString* documentDirectoryPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
	NSString* songId = [song valueForProperty:MPMediaItemPropertyPersistentID];
	NSString* songPath = [documentDirectoryPath stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.wav", songId]];
	
	// Song already exist at path, for now we remove it and log a message - in future we just return the song?
	if ([[NSFileManager defaultManager] fileExistsAtPath:songPath]) {
		[[NSFileManager defaultManager] removeItemAtPath:songPath error:nil];
		NSLog(@"NPAudioConverter Error: Song already exist at path! path=%@", songPath);
		return [_songKeyToPath objectForKey:songId];
	}

	AVAssetWriter*	assetWriter = [AVAssetWriter assetWriterWithURL:[NSURL fileURLWithPath:songPath]
														   fileType:AVFileTypeWAVE
															 error:&error];
	if([self checkError:error]) return nil;
	
	// Set the audio file properties
	AudioChannelLayout channelLayout;
	memset(&channelLayout, 0, sizeof(AudioChannelLayout));
	channelLayout.mChannelLayoutTag = kAudioChannelLayoutTag_Stereo;
	NSDictionary *outputSettings = [NSDictionary dictionaryWithObjectsAndKeys:
									[NSData dataWithBytes:&channelLayout length:sizeof(AudioChannelLayout)], AVChannelLayoutKey,
									[NSNumber numberWithInt:kAudioFormatLinearPCM], AVFormatIDKey,
									[NSNumber numberWithFloat:44100.0],				AVSampleRateKey,
									[NSNumber numberWithInt:2],						AVNumberOfChannelsKey,
									[NSNumber numberWithInt:16],					AVLinearPCMBitDepthKey,
									[NSNumber numberWithBool:NO],					AVLinearPCMIsNonInterleaved,
									[NSNumber numberWithBool:NO],					AVLinearPCMIsFloatKey,
									[NSNumber numberWithBool:NO],					AVLinearPCMIsBigEndianKey,
									nil];
	AVAssetWriterInput *assetWriterInput = [AVAssetWriterInput assetWriterInputWithMediaType:AVMediaTypeAudio
																			  outputSettings:outputSettings];
	// Check if we can write using those options
	if ([assetWriter canAddInput:assetWriterInput]) { [assetWriter addInput:assetWriterInput]; }
	else { NSLog(@"NPAudioConverter Error: Can't add assetwriter input!"); return nil; };
	
	assetWriterInput.expectsMediaDataInRealTime = NO;

	[assetWriter startWriting];
	[assetReader startReading];
	
	AVAssetTrack*	soundTrack = songAsset.tracks[0];
	CMTime			startTime = CMTimeMake(0, soundTrack.naturalTimeScale);
	[assetWriter startSessionAtSourceTime: startTime];
	
	__block UInt64 convertedByteCount = 0;
	dispatch_queue_t mediaInputQueue = dispatch_queue_create("mediaInputQueue", NULL);
	
	[assetWriterInput requestMediaDataWhenReadyOnQueue:mediaInputQueue
											usingBlock:
	 ^{
		 while( assetWriterInput.readyForMoreMediaData ) {
			 CMSampleBufferRef nextBuffer = [assetReaderOutput copyNextSampleBuffer];

			 if(nextBuffer) {
				 // Append buffer
				 [assetWriterInput appendSampleBuffer:nextBuffer];
				 convertedByteCount += CMSampleBufferGetTotalSampleSize(nextBuffer);
				 NSNumber* convertedByteCountNumber = [NSNumber numberWithLong:convertedByteCount];
				 
				 NSLog(@"%qu bytes converted", convertedByteCount);
			 } else {
				 [assetWriterInput markAsFinished];
				 [assetWriter finishWritingWithCompletionHandler:^{
					 if(assetWriter.status == AVAssetWriterStatusCompleted ) {
						 [_songKeyToPath setObject:songPath forKey:songId];
						 _lastFileWritten = songPath;
						 NSLog(@"NPAudioConverter wrote file at:\n%@", songPath);
					 }
				 }];
				 [assetReader cancelReading];
				 
				 NSDictionary*	outputFileAttributes = [[NSFileManager defaultManager] attributesOfItemAtPath:songPath error:nil];
				 NSNumber*		doneFileSize = [NSNumber numberWithLong:[outputFileAttributes fileSize]];
				 
				 NSLog (@"done. file size is %@", doneFileSize);
			 }
		 }
	 }];
	
	return nil;
}

-(BOOL)checkError:(NSError*)error {
	if(error) {
		NSLog(@"%@", [error localizedDescription]);
		return YES;
	}
	return NO;
}

@end
