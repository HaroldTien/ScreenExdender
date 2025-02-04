#import <Cocoa/Cocoa.h>
#include "capturing.h"
#include <string>
using namespace std;

//this code get the path of the wallpaper file.

string getWallPaperPath(){  
    @autoreleasepool {
        NSWorkspace *workspace = [NSWorkspace sharedWorkspace];
        // NSLog(@"%@", workspace);

        NSScreen *screen = [NSScreen mainScreen];
        // NSLog(@"%@", screen);

        NSURL *wallpaperURL = [workspace desktopImageURLForScreen:screen];
        // NSLog(@"%@", [wallpaperURL path]); 

        NSString *wallpaperPath = [wallpaperURL path];
        return [wallpaperPath UTF8String];
    }
}
