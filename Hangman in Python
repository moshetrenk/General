import fileinput
import random
#input file contains every word in the language of your choice (line separated)
chances = 7

class HangmanException(BaseException):
    pass

def decrementChancesException(a):
    if a == 0:
        raise HangmanException("")
    else:
        a -= 1

    return a


def output(i):
    man = ['    0  \n', '/', '|', '|', '\\\n', ' /  ', '\\']

    for a in range(0, i):
           print(man[a], end = " ")
    print("\n")


words = [line.strip().lower() for line in open('C:\\Users\\Moshe_000\\Desktop\\inFile.txt')]
word = words[random.randrange(0, len(words))]
matchedLetters = []
incorrectlyGuessed = []

for c in word:
    print ('_', end = " ")
print("\n")
#print(word)


def main():
        global chances
        
        if(chances > 0):
            letter = input("Guess a letter!\n")
        else:
            letter = ' '

        if letter in word:
            matchedLetters.append(letter)
        else:
            if letter in incorrectlyGuessed:
                print ("You already tried that")
            else:            
                try:
                    if(letter != '.'):
                        incorrectlyGuessed.append(letter)
                    chances = decrementChancesException(chances)
                    print ("ouch! that's not in the word, you have ", chances, " left")
                    if (chances > 0):
                        output(7 - chances)
                except HangmanException:
                    print("You are all out of chances and you will now be hanged.")
                    output(7)
                    print("The word you were looking for was ", word)
                    incorrectlyGuessed.pop()
                    print("You incorrectly guessed ", incorrectlyGuessed)
                    exit()
                


        loc = word.find(letter)
        a = 0
        numCharsOut = 0
        
        for i in range (0, len(word)):
            if(word[a] in matchedLetters):
                print (word[i], end = " ")
                numCharsOut += 1
            elif (loc != -1 and i == loc):
                print (word[loc], end = " ")
                numCharsOut += 1
            else:
                print('_', end = " ")
                
                
            a = a + 1

        print ("\n")

        if (numCharsOut == len(word)):
            print("You win after ", 7 - chances, " guesses!")
            exit()
            
while True:
    main()
