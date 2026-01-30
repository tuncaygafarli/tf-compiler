numbers = [42, 7, 19, 88, 3, 56, 12, 101, 34, 25, 67, 2, 91, 14, 48];
n = numbers.size();

i = 0;
while i < n {
    j = 0;
    while j < (n - i - 1) {
        if  numbers[j] > numbers[j + 1] {
            temp = numbers[j];
            numbers[j] = numbers[j + 1];
            numbers[j + 1] = temp;
        }
        j = j + 1;
    }
    i = i + 1;
}

log(numbers);