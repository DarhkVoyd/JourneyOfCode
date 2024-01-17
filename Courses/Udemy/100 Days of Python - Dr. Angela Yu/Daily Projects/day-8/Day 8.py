from art import logo
from os import system

alphabet = [
    "a",
    "b",
    "c",
    "d",
    "e",
    "f",
    "g",
    "h",
    "i",
    "j",
    "k",
    "l",
    "m",
    "n",
    "o",
    "p",
    "q",
    "r",
    "s",
    "t",
    "u",
    "v",
    "w",
    "x",
    "y",
    "z",
]

print(logo)


def caeser(text, shift, operation):
    transformed_text = ""
    if operation == "decode":
        shift *= -1
    for letter in text:
        if letter not in alphabet:
            transformed_text += letter
            continue
        transformed_text += alphabet[(ord(letter) - ord("a") + shift) % 26]
    print(f"The {operation}d text is {transformed_text}")


def user_input():
    direction = input("Type 'encode' to encrypt, type 'decode' to decrypt:\n").strip()
    text = input("Type your message:\n").lower().strip()
    shift = int(input("Type the shift number:\n").strip())
    if direction in ["encode", "decode"]:
        caeser(text, shift, direction)
    else:
        print("Invalid input")


def main():
    user_input()
    more = input("Type 'yes' if you want to go again. Otherwise type 'no':  ")
    while more != "no":
        system("clear")
        user_input()
        more = input("Type 'yes' if you want to go again. Otherwise type 'no':  ")

    print("Goodbye👋🏻.")


main()
