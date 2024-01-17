# Go to https://replit.com/@appbrewery/rock-paper-scissors-start?v=1

from random import randint
rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)
'''

paper = '''
    _______
---'   ____)____
          ______)
          _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''

#Write your code below this line 👇
gestures = [rock, paper, scissors]

human = int(input('What do you choose? Type 0 for Rock, 1 for Paper or 2 for Scissors.\n'))

if (human < 0 or human > 2):
    print('That\'s an invalid input. ')

print(gestures[human])

computer = randint(0, 2)

print('Computer chose:\n')
print(gestures[computer])

if ((human == 0 and computer == 2) or (human == 1 and computer == 0) or (human == 2 and computer == 1)):
    print("You Won!\n")
elif (human == computer):
    print("It's a Draw!")
else:
    print("You Lose!\n")



