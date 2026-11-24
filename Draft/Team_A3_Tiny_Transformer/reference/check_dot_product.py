"""Pure-Python reference for the first RTL test; no dependencies."""
a = [1, 2, 3, 4] + [0] * 12
b = [2, 1, 0, 3] + [0] * 12
answer = sum(x * y for x, y in zip(a, b))
assert answer == 16
print(f"PASS: dot product = {answer}")
