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


@end
