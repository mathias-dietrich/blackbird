//
//  ViewController.h
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "NSView+UI.h"

@interface ViewController : NSViewController


- (IBAction)btnWhite:(id)sender;
- (IBAction)btnBlack:(id)sender;
- (IBAction)btnFlip:(id)sender;

@property (nonatomic, retain) IBOutlet UI *ui;
@end



