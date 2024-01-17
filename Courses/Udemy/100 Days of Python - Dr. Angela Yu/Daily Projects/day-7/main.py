# Step 5
from hangman_art import logo, stages
from hangman_words import word_list
import random
import os

os.system("clear")  # For Mac and Linux
# os.system('cls')   # For Windows

chosen_word = random.choice(word_list)
word_length = len(chosen_word)

end_of_game = False
lives = 6

print(logo)
# Testing code
# print(f'Pssst, the solution is {chosen_word}.')

# Create blanks
display = []
used_letters = set()
for _ in range(word_length):
    display += "_"
print(f"{' '.join(display)}\n")
while not end_of_game:
    # Join all the elements in the list and turn it into a String.
    guess = input("Guess a letter: ").lower()
    if len(guess) != 1:
        print("Invalid Input! Enter a letter.")
        continue
    used_letters.add(guess)
    os.system("clear")  # For Mac and Linux
    # os.system('cls')   # For Windows
    if guess in display:
        print(f"You've already guessed {guess}!")
    # Check guessed letter
    for position in range(word_length):
        letter = chosen_word[position]
        # print(f"Current position: {position}\n Current letter: {letter}\n Guessed letter: {guess}")
        if letter == guess:
            display[position] = letter

    # Check if user is wrong.
    if guess not in chosen_word:
        os.system("clear")  # For Mac and Linux
        # os.system('cls')   # For Windows
        print(f"You guessed {guess}, that's not in the word. You lose a life.")
        lives -= 1
        if lives == 0:
            end_of_game = True
            print(f"The word was {chosen_word}.")
            print("You lose.")

    # Join all the elements in the list and turn it into a String.
    print(f"{' '.join(display)}\n")
    print(f"Used Letters: {' '.join(used_letters)}")

    # Check if user has got all letters.
    if "_" not in display:
        end_of_game = True
        print("You win.")

    print(stages[lives])
