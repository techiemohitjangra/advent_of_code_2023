package main

import (
	"bufio"
	"fmt"
	"log"
	"os"
	"strconv"
	"strings"
	"unicode"
	"unicode/utf8"
)

func solve1(line string) int64 {
	var first rune
	var last rune
	for _, char := range line {
		if unicode.IsDigit(char) {
			first = char
			break
		}
	}

	for i := utf8.RuneCountInString(line) - 1; i >= 0; i-- {
		var char rune = rune(line[i])
		if unicode.IsDigit(char) {
			last = char
			break
		}
	}

	var num = string([]rune{first, last})
	var result, err = strconv.ParseInt(num, 10, 64)
	if err != nil {
		fmt.Println("Error: ", err)
		return -1
	}
	return result
}

func solve2(line string) int64 {
	var lookup_table map[string]rune = make(map[string]rune)
	var charArr []rune = []rune(line)

	lookup_table["one"] = '1'
	lookup_table["two"] = '2'
	lookup_table["three"] = '3'
	lookup_table["four"] = '4'
	lookup_table["five"] = '5'
	lookup_table["six"] = '6'
	lookup_table["seven"] = '7'
	lookup_table["eight"] = '8'
	lookup_table["nine"] = '9'

	var first rune
	var last rune
	var firstIndex int = len(charArr)
	var lastIndex int = 0

	// first digits and its index
	for i, char := range charArr {
		if unicode.IsDigit(char) {
			first = char
			firstIndex = i
			break
		}
	}

	// first word and its index
	for key, value := range lookup_table {
		var index int = strings.Index(line, key)
		if index != -1 && index < firstIndex {
			first = value
			firstIndex = index
		}
	}

	lastIndex = -1

	// last digits and its index
	for i := len(charArr) - 1; i >= 0; i-- {
		var char rune = charArr[i]
		if unicode.IsDigit(char) {
			last = char
			lastIndex = i
			break
		}
	}

	// last word
	for key, value := range lookup_table {
		var index int = strings.LastIndex(line, key)
		if index != -1 && index > lastIndex {
			last = value
			lastIndex = index
		}
	}

	var num = string([]rune{first, last})
	num = strings.ReplaceAll(num, "\x00", "")
	var result, err = strconv.ParseInt(num, 10, 64)
	if err != nil {
		fmt.Println("Error: ", err)
		return -1
	}
	return result
}

func main() {
	var fName string = "./../input"

	var file, err = os.Open(fName)

	if err != nil {
		log.Fatalf("failed opening file: %s", err)
	}

	var result1 int64 = 0
	var result2 int64 = 0

	var reader = bufio.NewScanner(file)
	for reader.Scan() {
		line := reader.Text()
		result1 += solve1(line)
		result2 += solve2(line)
	}
	fmt.Println("Solution part 1: ", result1)
	fmt.Println("Solution part 2: ", result2)

	if err := reader.Err(); err != nil { fmt.Printf("Error reading file: %s", err)
	}

}
