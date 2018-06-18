//
//  NSView+UI.h
//  Blackbird
//
//  Created by Mathias Dietrich on 6/14/18.
//  Copyright © 2018 Mathias Dietrich. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface UI : NSView

@property (nonatomic, retain) NSImage *BlackBishop;
@property (nonatomic, retain) NSImage *WhiteBishop;
@property (nonatomic, retain) NSImage *BlackKing;
@property (nonatomic, retain) NSImage *WhiteKing;
@property (nonatomic, retain) NSImage *BlackKnight;
@property (nonatomic, retain) NSImage *WhiteKnight;
@property (nonatomic, retain) NSImage *BlackQueen;
@property (nonatomic, retain) NSImage *WhiteQueen;
@property (nonatomic, retain) NSImage *BlackPawn;
@property (nonatomic, retain) NSImage *WhitePawn;
@property (nonatomic, retain) NSImage *BlackRook;
@property (nonatomic, retain) NSImage *WhiteRook;

@property (nonatomic, retain) IBOutlet NSTextField *timeW;
@property (nonatomic, retain) IBOutlet NSTextField *timeB;
@property (nonatomic, retain) IBOutlet NSTextField *panel;
@property (nonatomic, retain) IBOutlet NSTextField *rule50;

@property (nonatomic, retain) IBOutlet NSTextField *w_eval;
@property (nonatomic, retain) IBOutlet NSTextField *b_eval;
@property (nonatomic, retain) IBOutlet NSTextField *enginePath;

@property (nonatomic, retain) IBOutlet NSTextField *fenField;

@property (nonatomic, retain) IBOutlet NSButton *btnPNG;
@property (nonatomic, retain) IBOutlet NSButton *btnEngine;
@property (nonatomic, retain) IBOutlet NSButton *btnDebug;
@property (nonatomic, retain) IBOutlet NSColorWell *pauseState;
@property (nonatomic, retain) IBOutlet NSTextField *boxMove;

@property (nonatomic, retain) IBOutlet NSComboBox *boxEngineWhite;
@property (nonatomic, retain) IBOutlet NSComboBox *boxEngineBlack;
@property (nonatomic, retain) IBOutlet NSComboBox *boxOpeningBook;

-(void)setup;
-(void)newWhite;
-(void)newBlack;
-(void)flip;

-(void)backwards;
-(void)forward;

-(void)update;

- (void)promoteQueen;
- (void)promoteRook;
- (void)promoteKnight;
- (void)promoteBishop;
- (void)debugMode;
- (void)clearDebug;
- (void)draw;

- (void)radioPng;
- (void)radioEngine;
- (void)radioDebug;
- (void)pause;

- (void)engineWhiteDidChange;
- (void)engineBlackDidChange;
- (void)openingBookDidChange;
@end


