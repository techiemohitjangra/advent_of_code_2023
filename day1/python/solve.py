

def part1(line: str) -> int:

    first = -1
    last = -1
    for char in line:
        if char.isdigit():
            if first == -1:
                first = char
            last = char

    return int(f"{first}{last}")


def part2(line: str) -> int:
    nums = {'one': 1, 'two': 2, 'three': 3, 'four': 4,
            'five': 5, 'six': 6, 'seven': 7, 'eight': 8, 'nine': 9}

    first: str = ''
    last: str = ''
    first_word_index: int = len(line)
    last_word_index: int = -1
    first_word: str = ''
    last_word: str = ''
    first_digit_index: int = len(line)
    last_digit_index: int = -1

    for index, char in enumerate(line):
        if char.isdigit():
            first_digit_index = index
            break

    for index, char in enumerate(line):
        if char.isdigit():
            last_digit_index = index

    for index in range(len(line)):
        if line[index:index+3] in nums.keys():
            first_word_index = index
            first_word = line[index: index+3]
            break
        if line[index:index+4] in nums.keys():
            first_word_index = index
            first_word = line[index: index+4]
            break
        if line[index:index+5] in nums.keys():
            first_word_index = index
            first_word = line[index: index+5]
            break

    for index in range(len(line[:-2])):
        if line[index:index+3] in nums.keys():
            last_word_index = index
            last_word = line[index: index+3]
        if line[index:index+4] in nums.keys():
            last_word_index = index
            last_word = line[index: index+4]
        if line[index:index+5] in nums.keys():
            last_word_index = index
            last_word = line[index: index+5]

    if (first_word_index < first_digit_index):
        first = str(nums[first_word])
    else:
        first = line[first_digit_index]

    if (last_word_index > last_digit_index):
        last = str(nums[last_word])
    else:
        last = line[last_digit_index]

    return int(str(first) + str(last))


if __name__ == "__main__":

    inputFile = "./../input"
    testFile = "./../test"
    result1 = 0
    result2 = 0
    with open(inputFile, 'r') as file:
        for line in file:
            # print(f"{part1(line)} -> {line}")
            # print(f"{part2(line)} -> {line}")
            result1 += part1(line)
            result2 += part2(line)

    print(f"Solution part1: {result1}")
    print(f"Solution part2: {result2}")
