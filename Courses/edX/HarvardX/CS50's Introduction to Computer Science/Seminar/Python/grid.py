def main():
    size = int(input("Size: "))
    grid(size)
    
def grid(a):
    for j in range(a):
        for i in range(a):
            print("#", end = "")
        print()
    
main()