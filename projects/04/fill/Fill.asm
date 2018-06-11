// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(LOOP)

// Read the keyboard
@KBD
D=M
@WHITE
D;JEQ
@BLACK
0;JMP

// Select black
(BLACK)
@COLOR
M=1
@PAINT
0;JMP

// Select white
(WHITE)
@COLOR
M=0

(PAINT)
@8192 // Get the max screen register
D=A
@IDX // Store it to the index
M=D

(PAINTLOOP)
@IDX // Get the current index
D=M
@SCREEN // Add the index to the start of the screen
D=D-1
D=D+A
@SCRPTR // Store in the screen pointer
M=D

@COLOR // Load the color
D=M
@PAINTWHITE
D;JEQ

(PAINTBLACK)
@SCRPTR
A=M // Move to screen location
// Set the color to black
D=!M
M=D|M
@ENDPAINTLOOP
0;JMP

(PAINTWHITE)
@SCRPTR
A=M // Move to screen location
// Set the color to white
D=!M
M=D&M

(ENDPAINTLOOP)
@IDX // Decrement the index
MD=M-1
@PAINTLOOP
D;JGT // Loop if index is greater than zero
@END
0;JMP

(END)
@LOOP
0;JMP
