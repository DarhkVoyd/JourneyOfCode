from art import logo, vs
from game_data import data
import random
from os import system


def get_option(used_option):
    option = random.choice(data)
    while used_option == option:
        option = random.choice(data)
        # print("option was already selected so new finding something new")
    return option


def game():
    is_game_over = False
    print(logo)

    option_a = get_option({})
    option_b = {}
    score = 0
    while not is_game_over:
        print(
            f"Compare A: {option_a['name']}, a {option_a['description']}, from {option_a['country']}. Psshhh-option_a['follower_count']"
        )
        print(vs)
        option_b = get_option(option_a)
        print(
            f"Compare B: {option_b['name']}, a {option_b['description']}, from {option_b['country']}. Psshhh-option_b['follower_count']"
        )
        guess = input("Who has more followers? Type 'A' or 'B': ")
        if (
            option_a["follower_count"] > option_b["follower_count"] and guess == "A"
        ) or (option_a["follower_count"] < option_b["follower_count"] and guess == "B"):
            score += 1
            option_a = option_b
            system("clear")
            print(logo)
            print(f"You're right! Current score: {score}")
        else:
            system("clear")
            print(logo)
            print(f"Sorry, that's wrong. Final score: {score}")
            is_game_over = True


game()
