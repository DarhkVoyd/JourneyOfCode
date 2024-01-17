def main():
    for i in range(1, 10):
        for j in range(1, 10):
            multiply(i, j)

def multiply(x, y):
    product = x * y
    print(x, "*", y, "=", product)

main()