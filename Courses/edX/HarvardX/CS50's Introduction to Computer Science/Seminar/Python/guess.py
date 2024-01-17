import random

def main():
    random = random.randint(1, 10)
    for i in range(3):
        guess = int(input("Guess: "))
        if guess == random:
            print("Congratulations! Your guess is correct.")
            break
        elif guess > random:
            print("Oops! Your guess is incorrect.")
            print("Your guess is larger than the number.")
        else:
            print("Oops! Your guess is incorrect.")
            print("Your guess is smaller than the number.")
            
