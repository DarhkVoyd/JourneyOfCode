cash = int(input("Cash: "))
coin = 0
while cash > 0:
    if cash >= 25:
        cash = cash - 25
        coin += 1
    elif cash >= 10 and cash < 25:
        cash = cash - 10
        coin += 1
    elif cash >= 5 and cash < 10:
        cash = cash - 5
        coin += 1
    elif cash >= 1 and cash < 5:
        cash = cash - 1
        coin += 1
print("Least number of required coins is/are",coin)