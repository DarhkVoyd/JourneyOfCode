import random

from art import logo

print(logo)

print("Welcome to the Number Guessing Game!")
print("I'm thinking of a number between 1 and 100.")

answer = random.randint(1, 100)

difficulty = input("Choose a difficulty. Type 'easy' or 'hard': ")
if difficulty == "easy":
    attempts = 10
elif difficulty == "hard":
    attempts = 5

while attempts > 0:
    print(f"You have {attempts} attempts remaining to guess the number.")
    guess = int(input("Make a guess: "))
    if guess == answer:
        print(f"You got it! The answer was {answer}.")
        break
    elif guess > answer:
        print("Too High!")
        attempts -= 1
    else:
        print("Too Low!")
        attempts -= 1

if attempts == 0:
    print("You've run out of guesses, you lose.")
    print(f"{answer}")
