# TODO
from cs50 import get_int

# Prompt User Input
while True:
    Height = get_int("Height: ")
    if Height >= 1 and Height <= 8:
        break

# Print Pattern
for i in range(Height):
    print(" " * (Height - i - 1), end="")
    print("#" * (i + 1), end="")
    print("  ", end="")
    print("#" * (i + 1))
