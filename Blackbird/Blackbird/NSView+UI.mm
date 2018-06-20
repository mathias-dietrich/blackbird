//
//  NSView+UI.m
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

// peaces from here: https://marcelk.net/chess/pieces/

#import "NSView+UI.h"
#import "engine/Engine.hpp"
#import "engine/Model.hpp"
#import "engine/MoveGen.hpp"

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
@synthesize timeW;
@synthesize timeB;
@synthesize mypanel;
@synthesize rule50;
@synthesize w_eval;
@synthesize b_eval;
@synthesize fenField;
@synthesize btnPNG;
@synthesize btnEngine;
@synthesize btnDebug;
@synthesize btnPGNDB;
@synthesize pauseStateWhite;
@synthesize pauseStateBlack;
@synthesize boxMove;
@synthesize boxEngineWhite;
@synthesize boxEngineBlack;
@synthesize boxOpeningBook;
@synthesize timeOutW;
@synthesize timeOutB;

Engine *engine;

-(void)update{
    
    if(engine->model->pausedWhite){
        pauseStateWhite.color =  [NSColor redColor];
    }else{
        pauseStateWhite.color = [NSColor greenColor];
    }
    if(engine->model->pausedBlack){
        pauseStateBlack.color =  [NSColor redColor];
    }else{
        pauseStateBlack.color = [NSColor greenColor];
    }
    switch(engine->model->winstate){
        case PNG:
        {
             mypanel.richText = true;
            btnPNG.state = NSControlStateValueOn;
            btnEngine.state = NSControlStateValueOff;
            btnDebug.state = NSControlStateValueOff;
            btnPGNDB.state = NSControlStateValueOff;
            
            NSString *text = [NSString stringWithCString:engine->model->moveList.c_str() encoding:[NSString defaultCStringEncoding]] ;
            mypanel.string = text;
            break;
        }
        case ENGINE:
        {
            btnPNG.state = NSControlStateValueOff;
            btnEngine.state = NSControlStateValueOn;
            btnDebug.state = NSControlStateValueOff;
            mypanel.string = [NSString stringWithCString:engine->model->engineList.c_str() encoding:[NSString defaultCStringEncoding]];
            btnPGNDB.state = NSControlStateValueOff;
            break;
        }
        case DEBUGWIN:
        {
            btnPNG.state = NSControlStateValueOff;
            btnEngine.state = NSControlStateValueOff;
            btnDebug.state = NSControlStateValueOn;
            mypanel.string = [NSString stringWithCString:engine->model->debugMsg.c_str() encoding:[NSString defaultCStringEncoding]];
            btnPGNDB.state = NSControlStateValueOff;
            break;
        }
        case PGNDB:
        {
            btnPNG.state = NSControlStateValueOff;
            btnEngine.state = NSControlStateValueOff;
            btnDebug.state = NSControlStateValueOff;
            btnPGNDB.state = NSControlStateValueOn;
            string t = "TODO write this section";
            mypanel.string = [NSString stringWithCString: t.c_str() encoding:[NSString defaultCStringEncoding]];
        }
    }
    
    // Rule 50
    NSMutableString *string = [NSMutableString stringWithString:@"rule50: "];
    [string appendString:[NSString stringWithFormat:@"%d:",engine->model->rule50Count]];
    rule50.stringValue = string;
    
    // Eval
    w_eval.stringValue = [NSString stringWithFormat:@"%d",engine->model->w_eval];
    b_eval.stringValue = [NSString stringWithFormat:@"%d",engine->model->b_eval];
    
    // Clocks
    if(engine->model->isDraw || engine->model->isMate){
        [self setNeedsDisplay:YES];
        return;
    }
    
    NSMutableString *sw = [NSMutableString stringWithString:@"White: "];
    int minW = engine->model->w_time / 60;
    int secW = engine->model->w_time - 60 * minW;
    if(secW<10){
        [sw appendString:[NSString stringWithFormat:@"%d:0%d",minW,secW]];
    }else{
        [sw appendString:[NSString stringWithFormat:@"%d:%d",minW,secW]];
    }
    timeW.stringValue = sw;
    
    int minB = engine->model->b_time / 60;
    int secB = engine->model->b_time - 60 * minB;
    NSMutableString *sb = [NSMutableString stringWithString:@"Black: "];
    if(secB<10){
        [sb appendString:[NSString stringWithFormat:@"%d:0%d",minB, secB]];
    }
    else{
        [sb appendString:[NSString stringWithFormat:@"%d:%d",minB, secB]];
    }
    timeB.stringValue = sb;
    
    // clock colors
    if(engine->model->board->whiteToMove){
        timeW.textColor = [NSColor redColor];
        timeB.textColor = [NSColor blackColor];
    }else{
        timeB.textColor = [NSColor redColor];
        timeW.textColor = [NSColor blackColor];
    }
    
    boxMove.stringValue = [NSString stringWithFormat:@"Move: %d", engine->model->board->moveId];
    fenField.stringValue = [NSString stringWithCString:engine->model->fenStr.c_str() encoding:[NSString defaultCStringEncoding]];
    [self setNeedsDisplay:YES];
}

- (void)setup
{
    NSLog(@"setup");

    NSString *bundlePath = [[NSBundle mainBundle] resourcePath];
    engine->model->resourceRoot = std::string([bundlePath UTF8String]);;
    
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
    [NSTimer scheduledTimerWithTimeInterval:1
                                     target:self
                                   selector:@selector(onTick:)
                                   userInfo:nil
                                    repeats:YES];
    
    NSThread* myThread = [[NSThread alloc] initWithTarget:self
                                                 selector:@selector(listenUCI:)
                                                   object:nil]; //how to pass callback block here?
    [myThread start];
    [self update];
}

-(void) listenUCI: (id) sender {
    engine->setupEngines();
}

-(void)onTick:(NSTimer *)timer {
    if(engine->model->runClock){
        if(engine->model->board->whiteToMove){
            engine->model->w_time++;
        }else{
            engine->model->b_time++;
        }
        [self update];
    }
}

- (void)drawRect:(CGRect)rect {

    if(engine == 0){
        engine =  Engine::Instance();
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
             int no =fildNo;
             if (engine->model->isFlipped){
                 no = 63 - fildNo;
             }
             [[[NSAttributedString alloc] initWithString:[NSString stringWithFormat:@"%d",no] attributes: attr] drawAtPoint:NSMakePoint(5 + offset +x * 100, 85 + offset +y * 100)];
            fildNo++;
        }
        flip = !flip;
    }
    
    // Letters
    
    NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:[NSFont fontWithName:@"Helvetica" size:20], NSFontAttributeName,textColor, NSForegroundColorAttributeName, nil];
    
    if(engine->model->isFlipped){
        [[[NSAttributedString alloc] initWithString:@"H" attributes: attributes] drawAtPoint:NSMakePoint(70, 0)];
        [[[NSAttributedString alloc] initWithString:@"G" attributes: attributes] drawAtPoint:NSMakePoint(170, 0)];
        [[[NSAttributedString alloc] initWithString:@"F" attributes: attributes] drawAtPoint:NSMakePoint(270, 0)];
        [[[NSAttributedString alloc] initWithString:@"E" attributes: attributes] drawAtPoint:NSMakePoint(370, 0)];
        [[[NSAttributedString alloc] initWithString:@"D" attributes: attributes] drawAtPoint:NSMakePoint(470, 0)];
        [[[NSAttributedString alloc] initWithString:@"C" attributes: attributes] drawAtPoint:NSMakePoint(570, 0)];
        [[[NSAttributedString alloc] initWithString:@"B" attributes: attributes] drawAtPoint:NSMakePoint(670, 0)];
        [[[NSAttributedString alloc] initWithString:@"A" attributes: attributes] drawAtPoint:NSMakePoint(770, 0)];
        
        [[[NSAttributedString alloc] initWithString:@"H" attributes: attributes] drawAtPoint:NSMakePoint( 70, 825)];
        [[[NSAttributedString alloc] initWithString:@"G" attributes: attributes] drawAtPoint:NSMakePoint(170, 825)];
        [[[NSAttributedString alloc] initWithString:@"F" attributes: attributes] drawAtPoint:NSMakePoint(270, 825)];
        [[[NSAttributedString alloc] initWithString:@"E" attributes: attributes] drawAtPoint:NSMakePoint(370, 825)];
        [[[NSAttributedString alloc] initWithString:@"D" attributes: attributes] drawAtPoint:NSMakePoint(470, 825)];
        [[[NSAttributedString alloc] initWithString:@"C" attributes: attributes] drawAtPoint:NSMakePoint(570, 825)];
        [[[NSAttributedString alloc] initWithString:@"B" attributes: attributes] drawAtPoint:NSMakePoint(670, 825)];
        [[[NSAttributedString alloc] initWithString:@"A" attributes: attributes] drawAtPoint:NSMakePoint(770, 825)];
        
        [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(5, 70)];
        [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(5, 170)];
        [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(5, 270)];
        [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(5, 370)];
        [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(5, 470)];
        [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(5, 570)];
        [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(5, 670)];
        [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(5, 770)];
        
        [[[NSAttributedString alloc] initWithString:@"8" attributes: attributes] drawAtPoint:NSMakePoint(830, 70)];
        [[[NSAttributedString alloc] initWithString:@"7" attributes: attributes] drawAtPoint:NSMakePoint(830, 170)];
        [[[NSAttributedString alloc] initWithString:@"6" attributes: attributes] drawAtPoint:NSMakePoint(830, 270)];
        [[[NSAttributedString alloc] initWithString:@"5" attributes: attributes] drawAtPoint:NSMakePoint(830, 370)];
        [[[NSAttributedString alloc] initWithString:@"4" attributes: attributes] drawAtPoint:NSMakePoint(830, 470)];
        [[[NSAttributedString alloc] initWithString:@"3" attributes: attributes] drawAtPoint:NSMakePoint(830, 570)];
        [[[NSAttributedString alloc] initWithString:@"2" attributes: attributes] drawAtPoint:NSMakePoint(830, 670)];
        [[[NSAttributedString alloc] initWithString:@"1" attributes: attributes] drawAtPoint:NSMakePoint(830, 770)];
    }else{
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
    }

    // Draw pices
    NSRect r = NSMakeRect(0, 0, 80, 80);
    
    for(int i=0; i < 64;i++){

        int pos = i;
        if(engine->model->isFlipped){
            pos = 63 - pos;
        }
         int piece = engine->model->board->fields[pos];
        
        int colum = i % 8;
        int row = i / 8;
        int xPos = 33 + colum * 100;
        int yPos = 33 + row * 100;
        
        // last target field
        if(i == engine->model->lastField){
            int xPos = 30 + colum * 100;
            int yPos = 30 + row * 100;
            NSRect r = NSMakeRect(xPos, yPos, 90, 90);
            NSBezierPath* circlePath = [NSBezierPath bezierPath];
            [circlePath appendBezierPathWithOvalInRect: r];
            
            NSColor *selColor = [NSColor colorWithCalibratedRed:0.3f green:1.0f blue:1.0f alpha:0.3f];
            [selColor set];
            
            [circlePath stroke];
            [circlePath fill];
        }
        
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
        
        if(engine->model->isFlipped){
            colum = 7- colum;
            row = 7 - row;
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
    if(engine->model->isMate || engine->model->isPromotion || engine->model->isDraw){
        return;
    }
     NSPoint curPoint = [self convertPoint:[theEvent locationInWindow] fromView:nil];
    int row = (((int)curPoint.x) - 25)/100 ;
    int col = (((int)curPoint.y) - 25)/100 ;
    int to = row + 8 * col;
    
    if(engine->model->isFlipped){
        to = 63 - to;
    }
    
    // user deselects same piece
    if(engine->model->selField == to){
        for(int i=0; i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }
        engine->model->selField = -1;
        [self update];
        return;
    }
    
    // User makes a move
    if(engine->model->selField > -1){
        if(engine->model->selFields[to] == OPTION){
            
            // move the board
            Ply ply3;
            ply3.from = engine->model->selField;
            ply3.to = to;
            engine->move(ply3);
            engine->model->clearSelection();
        }
        [self update];
        return;
    }
    
   // User Selects
    if(engine->model->board->whiteToMove && engine->model->board->fields[to] >0){
        for(int i=0;i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }
       
        // get possible moves
        uint64_t b = engine->gen->generate(engine->model->board,  to);
        vector<int>v = engine->gen->convertToPositions(b);
        bool haveMoves = false;
        vector<int>::iterator it;  // declare an iterator to a vector of strings
        for(it = v.begin(); it != v.end(); it++ ){
            engine->model->selFields[*it] = OPTION;
             haveMoves = true;
        }

        if(haveMoves){
            engine->model->selFields[to] = SELECTED;
            engine->model->selField = to;
        }
       [self update];
        return;
    }
    
    if(!engine->model->board->whiteToMove && engine->model->board->fields[to] < 0){
        for(int i=0;i < 64;i++){
            engine->model->selFields[i] = EMPTY;
        }

        // get possible moves
        uint64_t b = engine->gen->generate(engine->model->board,  to);
        vector<int>v = engine->gen->convertToPositions(b);
        vector<int>::iterator it;  // declare an iterator to a vector of strings
        
        bool haveMoves = false;
        for(it = v.begin(); it != v.end(); it++ ) {
            engine->model->selFields[*it] = OPTION;
            haveMoves = true;
        }
        
        if(haveMoves){
            engine->model->selFields[to] = SELECTED;
            engine->model->selField = to;
        }
       [self update];
    }
}

- (void)mouseUp:(NSEvent *)theEvent {

}


-(void)newWhite{
    engine->model->startTime = std::chrono::system_clock::now();
    engine->newWhite();
    engine->model->runClock = true;
    [self update];
}

-(void)newBlack{
    engine->model->startTime = std::chrono::system_clock::now();
    engine->newBlack();
    engine->model->runClock = true;
    [self update];
}

-(void)flip{
    engine->flip();
    [self update];
}

-(void)backwards{
    engine->backwards();
    [self update];
}

-(void)forward{
    engine->forward();
    [self update];
}

- (void)promoteQueen{
    engine->promoteQueen();
    [self update];
}

- (void)promoteRook{
    engine->promoteRook();
    [self update];
}

- (void)promoteKnight{
    engine->promoteKnight();
    [self update];
}

- (void)promoteBishop{
    engine->promoteBishop();
    [self update];
}

- (void)debugMode{
    engine->debugMode();
    [self update];
}

- (void)clearDebug{
    engine->clearDebug();
    [self update];
}

- (void)draw{
    engine->draw();
    [self update];
}
- (void)radioPng{
    engine->model->winstate = PNG;
     [self update];
}
- (void)radioEngine{
     engine->model->winstate = ENGINE;
     [self update];
}
- (void)radioDebug{
     engine->model->winstate = DEBUGWIN;
     [self update];
}

- (void)radioPGNDB{
    engine->model->winstate = PGNDB;
    [self update];
}

- (void)pauseBlack{
    engine->model->pausedBlack = ! engine->model->pausedBlack;
    [self update];
}
- (void)pauseWhite{
    engine->model->pausedWhite = ! engine->model->pausedWhite;
    [self update];
}
- (void)engineWhiteDidChange{
    string engineName = std::string([boxEngineWhite.stringValue UTF8String]);
    if(engineName.compare("User")==0){
        engineName = "";
    }
    engine->model->engineNameWhite = engineName;
    [self update];
}
- (void)engineBlackDidChange{
     string engineName = std::string([boxEngineBlack.stringValue UTF8String]);
    if(engineName.compare("User")==0){
        engineName = "";
    }
    engine->model->engineNameBlack = engineName;
    [self update];
}
- (void)openingBookDidChange{
     string bookName = std::string([boxOpeningBook.stringValue UTF8String]);
    if(bookName.compare("No Opening Book")==0){
        bookName = "";
        engine->model->useBook = false;
    }
    engine->model->bookName = bookName;
    engine->model->useBook = true;
    [self update];
}
@end
