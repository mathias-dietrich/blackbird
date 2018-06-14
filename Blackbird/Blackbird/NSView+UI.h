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



-(void)setup;
-(void)newWhite;
-(void)newBlack;
-(void)flip;

@end


