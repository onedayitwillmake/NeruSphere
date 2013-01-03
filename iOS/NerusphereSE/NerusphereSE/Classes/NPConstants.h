/**
 * NPConstants is not a class, but simply a file that contains global constants used in the game
 * The .m contains variables that must be instantiated at compile time
 * The .h contains numeric constants
 *
 * For any numeric constants that contain a /2 in them, this is because we're using the number from illustrator
 * 
 *	Examples in header:
		static const NSUInteger NPkPtsPointsPerPiece = 200;
		extern NSString* const NPkEventGameDidEnd;
 
		 @interface NPConstants
			+(UIColor*)hotPinkColor; // Used for choose the...
		 @end
	Examples of above in implementation
		NSString* const NPkEventGameDidEnd = @"NPkEventGameDidEnd";
		
		+(UIColor*)hotPinkColor {
			static UIColor* color = nil;
			if(!color) color = [UIColor colorWithRed: 232.0f/255.0f green:10.0f/255.0f blue:137.0f/255 alpha:1.0f];

			return color;
		}
 */
#pragma mark - ViewController Identifiers
extern NSString* const NPkViewControllerIdentifierNPVisualizer;
extern NSString* const NPkViewControllerIdentifierNPAudioPlayer;
extern NSString* const NPkViewControllerIdentifierNPSettingsPanel;

// Place colors or other objects that cannot be statically allocated outside of a class below
@interface NPkConstants
/// Returns either the iphone or ipad storyboard based on a simple runtime check
+(NSString *)storyboardName;
+(const char *)bundlePathAsCString;
@end