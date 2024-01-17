import random

def main():
    
    # count down to the new year
    number = random.randint(5, 15)
    countdown(number)
    print("Happy New Year")
    
def countdown(n):
    for i in range(n):
        print(n - i)

main()