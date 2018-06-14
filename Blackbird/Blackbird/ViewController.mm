//
//  ViewController.m
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#import "ViewController.h"
#import "Engine.hpp"

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (IBAction)btnWhite:(id)sender{
    Engine::Instance()->newWhite();
}

- (IBAction)btnBlack:(id)sender{
     Engine::Instance()->newBlack();
}

- (IBAction)btnFlip:(id)sender{
    Engine::Instance()->flip();
}


@end
