# CheckMate
The problem: Enter the coordinates of the black king, white king, white queen, white rook, white knight.
The program should tell if there is a way out of mate if the game starts in black.
Solution: The game will have not case of mate if and only if the game is in blockade situation at the start.
Օtherwise there is always a case of mate when there is one king on the board and 4 pieces by the opponent,
even when the King of Blacks takes one of the white pieces on the first step,there is a case of mate with the remaining 3 figures.


Because there is only 5 figure I will not generate the board.

Program description: At first, the player will enter the coordinates of the king of Blacks.
Then the coordinates of the imported position will be kept in the vector.
Then the player will enter the white coordinates, which will also be stored in the vector.
Then it will be checked that all positions around black King are in check, the position of the king is not and 
The Black king cannot take any white pieces
