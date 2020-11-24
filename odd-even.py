
numbers = [5, 1, 4, 8, 12, 7, 4, 9, 11, 14, 32, 2, 7, 12]
Odd = []
Even = [] 

num_len = len(numbers)

for i in range(num_len):
    if ((numbers[i]%2) == 0):
        Even.append(numbers[i])
    else:
        Odd.append(numbers[i])

print "numbers:", numbers
print "Odd: ", Odd
print "Even: ", Even
