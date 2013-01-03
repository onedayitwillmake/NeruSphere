/**
 * NPConstants is not a class, but simply a file that contains global constants used in the game
 * The .m contains variables that must be instantiated at compile time
 * The .h contains numeric constants
 */

#import "NPConstants.h"

NSString* const NPkViewControllerIdentifierNPVisualizer = @"NPVisualizerViewController";
NSString* const NPkViewControllerIdentifierNPAudioPlayer = @"NPPlaylistEditor";
NSString* const NPkViewControllerIdentifierNPSettingsPanel = @"NPVisualizerSettings";
@implementation NPkConstants
+(NSString*)storyboardName {
	if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
	    return @"MainStoryboard_iPhone";
	} else {
	    return @"MainStoryboard_iPad";
	}
}

+(const char *)bundlePathAsCString {
	return [[[NSBundle mainBundle] bundlePath] cStringUsingEncoding:NSUTF8StringEncoding];
}
@end