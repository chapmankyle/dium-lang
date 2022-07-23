/-
 - Performs the fizzbuzz computation for a given number.
 - @param {num} x Number to compute fizzbuzz for.
 - @returns {string} "Fizz", "Buzz", "FizzBuzz" or the given number.
 -/
func fizzbuzz(num x) => string {
	if x % 3 == 0 and x % 5 == 0 {
		return "Fizzbuzz"
	} elsif x % 3 == 0 {
		return "Fizz"
	} elsif x % 5 == 0 {
		return "Buzz"
	} else {
		return string(x)
	}
}

// Main method
func main() => void {
	num limit = 100

	/-
	 - Go through and print the fizzbuzz
	 - representation of each number
	 -/
	for num idx in range(1, limit + 1, 1) { // (int idx = 1; i < limit + 1; i++)
		println(fizzbuzz(idx))
	}

	// Alternative using while
	/-
	 - num idx = 1
	 - while idx <= limit {
	 -     println(fizzbuzz(idx))
	 -     idx += 1
	 - }
	 -/

	exit(0)
}
