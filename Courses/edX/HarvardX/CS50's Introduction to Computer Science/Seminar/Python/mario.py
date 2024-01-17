def main():
    steps = int(input("Enter Steps: "))
    stairs(steps)

def stairs(n):
    for i in range(1, n + 1):
        for j in range(n - i):
            print(" ", end = "")
        for k in range(i):
            print("#", end = "")
        print()

main()
