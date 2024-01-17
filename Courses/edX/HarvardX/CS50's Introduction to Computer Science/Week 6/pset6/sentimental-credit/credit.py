# TODO
from cs50 import get_string
from sys import exit
import re

# Prompt User Input
card = get_string("Number: ")

# Amex 15 Digits, Starts with - 34 or 37
# Visa 13 or 16 Digits, Starts with - 4
# Master 16 Digits, Starts with - 51 to 55

# Calculating Digits
digits = len(card)

# Validating Basic Conditions
if ((digits not in [13, 15, 16]) or ((card[0] != '4') and (card[0] != '3' and card[1] not in ['4', '7']) and (card[0] != '5' and card[1] not in ['1', '2', '3', '4', '5']))):
    print("INVALID")
    exit(1)

rev = card[::-1]
sum = 0

# Luhn Algorithm
for i in range(digits):
    if (i % 2 == 0):
        sum = sum + int(rev[i])
    else:
        sum = sum + ((int(rev[i]) * 2) % 10)
for i in range(digits):
    if (i % 2 == 1):
        sum = sum + (((int(rev[i]) * 2) // 10) % 10)

# Print Result
if (sum % 10 == 0):
    if (card[0] == '4'):
        print("VISA")
    elif (card[0] == '3' and card[1] in ['4', '7']):
        print("AMEX")
    else:
        print("MASTERCARD")
else:
    print("INVALID")
