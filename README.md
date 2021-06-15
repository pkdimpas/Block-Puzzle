# Block-Puzzle

## Challenge by Hideki Ito

Create a program that erase blocks from the puzzle board based on the given criteria and then count the score.

Example:   Board size: 6 x 6, Criteria to erase blocks – connected at least 3 blocks

![image](https://user-images.githubusercontent.com/28287818/122038665-6d13b380-ce08-11eb-8038-8056e43743ef.png)


## Rules
1. At the beginning, the puzzle board is filled with blocks with number 1 to 9. 
2. Size of the board and blocks data are provided by the input test data.
3. Based on the minimum number of connected blocks with same number required to erase, erase the blocks. All erasable blocks are erased from the puzzle board.  If there’s no block to erase, then proceed to step 6
4. Remaining blocks fall down by gravity if there’s any empty spaces underneath.
5. Once all blocks are fallen down, go back to step 3.
6. When you erase connected blocks, you get score based on the number of the block and the number of  connected blocks.   For example, if the blocks above are erased, it scores 5 x 4 = 20 point.

    ![image](https://user-images.githubusercontent.com/28287818/122039595-6a658e00-ce09-11eb-993e-9b9787f7e47a.png)

7. At the end of a puzzle, display the final blocks and total point you got from the puzzle.

### Connected block
  Connected block means blocks that are connected either vertically or horizontally, not diagonally.
  ![image](https://user-images.githubusercontent.com/28287818/122039996-e4961280-ce09-11eb-8280-70c951c93f04.png)
### Input Data is a text file like below (sample)

Each block data is separated by single space. We don’t use abusing data. 
![image](https://user-images.githubusercontent.com/28287818/122040515-7a31a200-ce0a-11eb-8310-a457856d3c9a.png)

### Example

![image](https://user-images.githubusercontent.com/28287818/122043169-a0a50c80-ce0d-11eb-8b79-807c695d6892.png)

## Program Specification
* Program must output the followings for each puzzle.
* Original block size (width and height), minimum number of connected blocks required to erase.
* Original block data
* Final block data (use period ‘.’ for no block spaces)
* Total point (score)
* One empty line ( do not forget! )

  ![image](https://user-images.githubusercontent.com/28287818/122044039-9d5e5080-ce0e-11eb-92cf-2bbf9d09d289.png)

* Input file has end of puzzle line (which is 0 0 0 for the place where width, height and minimum blocks are specified).
* Maximum width and height of the puzzle board is 30 x 30. 
* Valid range of minimum connected blocks required is 1 to 900.
* Test files to be used for contest judgement is within these limitations and we do not use any abusing test files.
* Your program must be console based program.
* Your source code file name should be block-(yourname).c
  ``` 
    For example      block-hideki.c
    Usage:
    block-hideki (input puzzle data filename)
  ```

* If input file name is not specified, display the usage on the console and exit.
* If your program encounter any errors, display the proper error message and exit your program.


