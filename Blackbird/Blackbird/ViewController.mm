//
//  ViewController.m
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#import "ViewController.h"

@implementation ViewController

@synthesize ui;

- (IBAction)btnSetEngine:(id)sender{
    
}

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (IBAction)btnWhite:(id)sender{
    [ui newWhite];
}

- (IBAction)btnBlack:(id)sender{
     [ui newBlack];
}

- (IBAction)btnFlip:(id)sender{
    [ui flip];
}

- (IBAction)btnForwards:(id)sender{
     [ui forward];
}

- (IBAction)btnBackwards:(id)sender{
     [ui backwards];
}

- (IBAction)btnQueen:(id)sender{
     [ui promoteQueen];
}
- (IBAction)btnRook:(id)sender{
     [ui promoteRook];
}
- (IBAction)btnKnight:(id)sender{
     [ui promoteKnight];
}
- (IBAction)btnBishop:(id)sender{
     [ui promoteBishop];
}
- (IBAction)btnDebug:(id)sender{
     [ui debugMode];
}
- (IBAction)btnClear:(id)sender{
     [ui clearDebug];
}
- (IBAction)btnDraw:(id)sender{
     [ui draw];
}

- (IBAction)radioPng:(id)sender{
    [ui radioPng];
}
- (IBAction)radioDebug:(id)sender{
    [ui radioDebug];
}
- (IBAction)radioEngine:(id)sender{
    [ui radioEngine];
}
- (IBAction)pause:(id)sender{
    [ui pause];
}

- (IBAction)engineWhiteDidChange:(id)sender{
    [ui engineWhiteDidChange];
}
- (IBAction)engineBlackDidChange:(id)sender{
    [ui engineBlackDidChange];
}
- (IBAction)openingBookDidChange:(id)sender{
    [ui openingBookDidChange];
}
@end
