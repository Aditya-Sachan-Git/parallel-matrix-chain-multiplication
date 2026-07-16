import random

n = int(input("Enter the value of n (number of dimensions): "))
values = [random.randint(1, 1000) for _ in range(n)]

with open("input.txt", "w") as f:
    f.write(f"{n}\n")
    f.write(" ".join(map(str, values)))

print(f"Generated input.txt with {n} values between 1-1000")
