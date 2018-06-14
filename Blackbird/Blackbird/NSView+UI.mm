//
//  NSView+UI.m
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

// peaces from here: https://marcelk.net/chess/pieces/

#import "NSView+UI.h"
#import "engine/Engine.cpp"
#import "engine/Const.h"

@implementation UI

@synthesize BlackBishop;
@synthesize WhiteBishop;
@synthesize BlackKing;
@synthesize WhiteKing;
@synthesize BlackKnight;
@synthesize WhiteKnight;
@synthesize BlackQueen;
@synthesize WhiteQueen;
@synthesize BlackPawn;
@synthesize WhitePawn;
@synthesize BlackRook;
@synthesize WhiteRook;

Engine *engine;

- (void)setup
{
    NSLog(@"setup");
    // do any initialization that's common to both -initWithFrame:
    // and -initWithCoder: in this method
    
    BlackBishop = [NSImage imageNamed:@"BlackBishop.png"];
    WhiteBishop = [NSImage imageNamed:@"WhiteBishop.png"];
    BlackKing = [NSImage imageNamed:@"BlackKing.png"];
    WhiteKing = [NSImage imageNamed:@"WhiteKing.png"];
    BlackKnight = [NSImage imageNamed:@"BlackKnight.png"];
    WhiteKnight = [NSImage imageNamed:@"WhiteKnight.png"];
    BlackQueen = [NSImage imageNamed:@"BlackQueen.png"];
    WhiteQueen = [NSImage imageNamed:@"WhiteQueen.png"];
    BlackPawn = [NSImage imageNamed:@"BlackPawn.png"];
    WhitePawn = [NSImage imageNamed:@"WhitePawn.png"];
    BlackRook = [NSImage imageNamed:@"BlackRook.png"];
    WhiteRook = [NSImage imageNamed:@"WhiteRook.png"];
    
    engine->startPos();
}


- (void)drawRect:(CGRect)rect {

    if(engine == 0){
        engine = new Engine();
    }
    
    if(! engine->model->hasLoaded){
        [self setup];
        engine->model->hasLoaded = true;
    }
    
    // Create Colors
    NSColor *textColor = [NSColor colorWithCalibratedRed:0.3 green:0.3 blue:0.3 alpha:1.0f];
    NSColor *frameColor = [NSColor colorWithCalibratedRed:0.9 green:0.9 blue:0.9 alpha:1.0f];
    
    NSColor *bgColor = [NSColor colorWithCalibratedRed:0.7 green:0.7 blue:1 alpha:1.0f];
    NSColor *fieldColor = [NSColor colorWithCalibratedRed:0.4 green:0.4 blue:0.7 alpha:1.0f];
    
     NSColor *noColor = [NSColor colorWithCalibratedRed:1 green:1 blue:1 alpha:1.0f];
   
    // background
    [frameColor set];
    NSRectFill(rect);

    // Fields
    bool flip = false;
    int offset = 25;
    
    int fildNo = 0;
    
    NSDictionary *attr = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:11], NSFontAttributeName,noColor, NSForegroundColorAttributeName, nil];
    
     for(int y=0;y<8;y++){
         for(int x=0;x<8;x++){
            if(flip){
                [bgColor set];
            }else{
                 [fieldColor set];
            }
            CGRect sq = CGRectMake(offset + x * 100, offset + y * 100, 100, 100);
            NSRectFill(sq);
            
            flip = !flip;
            
             [[[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d",fildNo] attributes: attr] drawAtPoint:NSMakePoint(5 + offset +x * 100, 85 + offset +y * 100)];
            fildNo++;
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
    
    [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(5, 70)];
    [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(5, 170)];
    [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(5, 270)];
    [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(5, 370)];
    [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(5, 470)];
    [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(5, 570)];
    [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(5, 670)];
    [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(5, 770)];
    
    [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(830, 70)];
    [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(830, 170)];
    [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(830, 270)];
    [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(830, 370)];
    [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(830, 470)];
    [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(830, 570)];
    [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(830, 670)];
    [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(830, 770)];


    // Draw pices
    NSRect r = NSMakeRect(0, 0, 80, 80);
    

    for(int i=0; i < 64;i++){
        int piece = engine->model->fields[i];
        
        int colum = i % 8;
        int row = i / 8;
        int xPos = 33 + colum * 100;
        int yPos = 33 + row * 100;
        
        switch(piece){
            case EMPTY:
                break;
                
            case W_ROOK:
                 [WhiteRook drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case W_KNIGHT:
                 [WhiteKnight drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case W_BISHOP:
                [WhiteBishop drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case W_QUEEN:
                 [WhiteQueen drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case W_KING:
                 [WhiteKing drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case W_PAWN:
                 [WhitePawn drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_ROOK:
                 [BlackRook drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_KNIGHT:
                 [BlackKnight drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_BISHOP:
                 [BlackBishop drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_QUEEN:
                 [BlackQueen drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_KING:
                 [BlackKing drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
            case B_PAWN:
                 [BlackPawn drawAtPoint:NSMakePoint(xPos,yPos) fromRect:r operation:NSCompositingOperationSourceAtop fraction:1.0];
                break;
                
        }
        
        if(engine->model->selFields[i] == SELECTED){
            int xPos = 25 + colum * 100;
            int yPos = 25 + row * 100;
             NSRect r = NSMakeRect(xPos, yPos, 100, 100);
            
            NSColor *selColor = [NSColor colorWithCalibratedRed:0.0f green:1.0f blue:1.0f alpha:1.0f];
            [selColor set];
             NSFrameRectWithWidth(r,3);
            
        }
        if(engine->model->selFields[i] == OPTION){
            int xPos = 50 + colum * 100;
            int yPos = 50 + row * 100;
            NSRect r = NSMakeRect(xPos, yPos, 50, 50);
            
            NSBezierPath* circlePath = [NSBezierPath bezierPath];
            [circlePath appendBezierPathWithOvalInRect: r];
            
            NSColor *selColor = [NSColor colorWithCalibratedRed:1.0f green:1.0f blue:1.0f alpha:0.5f];
            [selColor set];
            
            [circlePath stroke];
            [circlePath fill];
        }
    }
}

- (void)mouseDown:(NSEvent *)theEvent {
     NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    int row = (((int)curPoint.x) - 25)/100 ;
    int col = (((int)curPoint.y) - 25)/100 ;
    int pos = row + 8 * col;
    NSLog(@"Position: %i", pos);
    
    // make a move
    if(engine->model->selField > -1){
        int figure = engine->model->fields[engine->model->selField];
        engine->model->fields[engine->model->selField] = EMPTY;
        engine->model->fields[pos] = figure;
        engine->model->whiteToMove = ! engine->model->whiteToMove;
        [self setNeedsDisplay:YES];
        for(int i=0;i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }
        engine->model->selField = -1;
        return;
    }
    
    if(engine->model->selField == pos){
        engine->model->selFields[pos] = EMPTY;
        [self setNeedsDisplay:YES];
        engine->model->selField = -1;
        return;
    }
    
    if(engine->model->whiteToMove && engine->model->fields[pos] >0){
        for(int i=0;i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }
        engine->model->selFields[pos] = SELECTED;
        engine->model->selField = pos;
        [self setNeedsDisplay:YES];
    }
    
    if(!engine->model->whiteToMove && engine->model->fields[pos] < 0){
        for(int i=0;i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }
        engine->model->selFields[pos] = SELECTED;
        engine->model->selField = pos;
        [self setNeedsDisplay:YES];
    }
}

- (void)mouseUp:(NSEvent *)theEvent {
    NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    int row = (((int)curPoint.x) - 25)/100 ;
    int col = (((int)curPoint.y) - 25)/100 ;
    int pos = row + 8 * col;
    NSLog(@"Position: %i", pos);
}



@end