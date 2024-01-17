from os import system

from art import logo

print(logo)
aution_data = {}
has_aution_ended = False
while not has_aution_ended:
    participant = input("What is your name? ").strip().lower()
    bid = int(input("What is your bid? $").strip())
    aution_data[participant] = bid
    has_aution_ended = (
        False
        if input("Are there any other bidders? Type 'yes' or 'no'. ").strip().lower()
        == "yes"
        else True
    )
    if not has_aution_ended:
        system("clear")

max = {
    "user": "",
    "bid": 0,
}
for key in aution_data:
    if aution_data[key] > max["bid"]:
        max["bid"] = aution_data[key]
        max["user"] = key
system("clear")
print(f"The winner of the bid is {max['user']} with the bid of {max['bid']}")
