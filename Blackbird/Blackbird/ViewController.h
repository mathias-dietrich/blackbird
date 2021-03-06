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

- (IBAction)btnForwards:(id)sender;
- (IBAction)btnBackwards:(id)sender;


- (IBAction)btnQueen:(id)sender;
- (IBAction)btnRook:(id)sender;
- (IBAction)btnKnight:(id)sender;
- (IBAction)btnBishop:(id)sender;


- (IBAction)btnDebug:(id)sender;
- (IBAction)btnClear:(id)sender;
- (IBAction)btnDraw:(id)sender;
- (IBAction)btnSetFen:(id)sender;


- (IBAction)radioPng:(id)sender;
- (IBAction)radioDebug:(id)sender;
- (IBAction)radioEngine:(id)sender;
- (IBAction)radioPGNDB:(id)sender;
- (IBAction)pauseBlack:(id)sender;
- (IBAction)pauseWhite:(id)sender;

- (IBAction)engineWhiteDidChange:(id)sender;
- (IBAction)engineBlackDidChange:(id)sender;
- (IBAction)openingBookDidChange:(id)sender;

@property (nonatomic, retain) IBOutlet UI *ui;
@end



