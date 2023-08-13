import sys
import random
from enum import Enum

class RPS(Enum):
    Rock = 1
    Paper = 2
    Scissors = 3

line1 = "************************************"
line2 = "*                                  *"
line3 = "***     Welcome To The Play      ***"
line4 = "***   Rock - Paper - Scissors    ***"

print(line1)
print(line2)
print(line3)
print(line4)
print(line2)
print(line1)

print("")
playerchoice = input("Enter...\n1 for Rock\n2 for Paper\n3 for Sicissors:\n\n")
player = int(playerchoice) 

if player > 1 or player > 3 or player == 0:
    sys.exit("You must enter 1,2 or 3.\n")

#if player >= 'a' or player <= 'z':
#    sys.exit("You must enter 1,2 or 3.\n")

computerchoice = random.choice("123")
computer = int(computerchoice)

print("\nYou chose " + str(RPS(player)).replace('RPS.','') + ".")
print("Python chose " + str(RPS(computer)).replace('RPS.','')  + ".\n")

if player == 1 and computer == 3:
    print("You Win!\n")

elif player == 2 and computer == 1:
    print("You Win!\n")

elif player == 3 and computer == 2:
    print("You Win!\n")

elif player == computer:
    print("** Tie Game **\n")

else:
    print(" -- Python Wins -- \n")
