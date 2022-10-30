# Get_Next_Line

## GENERAL

Scope of this programm is to return a line, read from a file descriptor or NULL if there are no new lines available.
It will be read one line at the time.
On top of that our programm should be able to handle bot the cases reading from a file or from the standard input.

## COMPILATION

To compile it should be used the flag: -D BUFFER_SIZE=xx, with x, the value of the BUFFERSIZE that could be a value between 1 and 10.000.
This project is was useful to learn a new concept in C programming: static variables.

## NORMINETTE

As all other C projects at the 42 school, the code has to written in accordance with the norm:
- only 25 lines per function
- only 5 functions per file
- the only predefined functions allowed for this project are: read, malloc and free.

## RESULT

<img width="1936" alt="Ergebnis" src="https://user-images.githubusercontent.com/85942176/135713148-1a0490a1-d313-4056-93ea-96183c07ee74.png">

## TESTING

git@github.com:Tripouille/gnlTester.git
