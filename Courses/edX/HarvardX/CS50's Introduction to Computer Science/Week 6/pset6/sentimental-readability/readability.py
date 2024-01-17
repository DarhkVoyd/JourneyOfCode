# TODO
from cs50 import get_string
import re

text = get_string("Text: ")

# Initializing Varibles for Algorithm
letters = words = sentences = 0

# Calculating Varibles
for i in range(0, len(text)):
    if text[i].isalpha():
        letters = letters + 1
    elif text[i] == " ":
        words = words + 1
    elif text[i] == "?" or text[i] == "." or text[i] == "!":
        sentences = sentences + 1
words = words + 1
print(f"Words: {words} Letters: {letters} Sentences: {sentences}")

# Algorithm
index = (0.0588 * ((letters / words) * 100) -
         0.296 * ((sentences / words) * 100) - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 1 and index < 16:
    print(f"Grade {index:.0f}")
else:
    print("Grade 16+")
