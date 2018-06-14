//
//  NSView+UI.m
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#import "NSView+UI.h"

@implementation UI

- (void)drawRect:(CGRect)rect {
    
    // Create Colors
    NSColor *textColor = [NSColor colorWithCalibratedRed:0.3 green:0.3 blue:0.3 alpha:1.0f];
    NSColor *frameColor = [NSColor colorWithCalibratedRed:0.9 green:0.9 blue:0.9 alpha:1.0f];
    NSColor *bgColor = [NSColor colorWithCalibratedRed:0.5 green:0.5 blue:1 alpha:1.0f];
    NSColor *fieldColor = [NSColor colorWithCalibratedRed:0.2 green:0.2 blue:0.5 alpha:1.0f];
   
    // background
    [frameColor set];
    NSRectFill(rect);

    // Fields
    bool flip = false;
    int offset = 25;
    for(int x=0;x<8;x++){
        for(int y=0;y<8;y++){
            if(flip){
                [bgColor set];
            }else{
                 [fieldColor set];
            }
            CGRect sq = CGRectMake(offset + x * 100, offset + y * 100, 100, 100);
            NSRectFill(sq);
            
            flip = !flip;
        }
         flip = !flip;
    }
    
    // Letters
    
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:20], NSFontAttributeName,textColor, NSForegroundColorAttributeName, nil];
    
    [[[NSAttributedString alloc] initWithString:@"A" attributes: attributes] drawAtPoint:NSMakePoint(70, 0)];
    [[[NSAttributedString alloc] initWithString:@"B" attributes: attributes] drawAtPoint:NSMakePoint(170, 0)];
    [[[NSAttributedString alloc] initWithString:@"C" attributes: attributes] drawAtPoint:NSMakePoint(270, 0)];
    [[[NSAttributedString alloc] initWithString:@"D" attributes: attributes] drawAtPoint:NSMakePoint(370, 0)];
    [[[NSAttributedString alloc] initWithString:@"E" attributes: attributes] drawAtPoint:NSMakePoint(470, 0)];
    [[[NSAttributedString alloc] initWithString:@"F" attributes: attributes] drawAtPoint:NSMakePoint(570, 0)];
    [[[NSAttributedString alloc] initWithString:@"G" attributes: attributes] drawAtPoint:NSMakePoint(670, 0)];
    [[[NSAttributedString alloc] initWithString:@"H" attributes: attributes] drawAtPoint:NSMakePoint(770, 0)];
    
    [[[NSAttributedString alloc] initWithString:@"A" attributes: attributes] drawAtPoint:NSMakePoint( 70, 825)];
    [[[NSAttributedString alloc] initWithString:@"B" attributes: attributes] drawAtPoint:NSMakePoint(170, 825)];
    [[[NSAttributedString alloc] initWithString:@"C" attributes: attributes] drawAtPoint:NSMakePoint(270, 825)];
    [[[NSAttributedString alloc] initWithString:@"D" attributes: attributes] drawAtPoint:NSMakePoint(370, 825)];
    [[[NSAttributedString alloc] initWithString:@"E" attributes: attributes] drawAtPoint:NSMakePoint(470, 825)];
    [[[NSAttributedString alloc] initWithString:@"F" attributes: attributes] drawAtPoint:NSMakePoint(570, 825)];
    [[[NSAttributedString alloc] initWithString:@"G" attributes: attributes] drawAtPoint:NSMakePoint(670, 825)];
    [[[NSAttributedString alloc] initWithString:@"H" attributes: attributes] drawAtPoint:NSMakePoint(770, 825)];
    
    [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(0, 70)];
    [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(0, 170)];
    [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(0, 270)];
    [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(0, 370)];
    [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(0, 470)];
    [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(0, 570)];
    [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(0, 670)];
    [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(0, 770)];
    
    [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(830, 70)];
    [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(830, 170)];
    [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(830, 270)];
    [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(830, 370)];
    [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(830, 470)];
    [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(830, 570)];
    [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(830, 670)];
    [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(830, 770)];


}



@end
