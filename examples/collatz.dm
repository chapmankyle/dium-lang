/-
 - Performs the Collatz conjecture on a given number.
 - @param {num} x Number to perform the Collatz conjecture on.
 - @param {bool} show `true` to print the result, `false` otherwise.
 - @returns {num} Number of iterations it took to reach 1.
 -/
func collatz(num x, bool show) => num {
	num count = 1

	if show {
		println(x)
	}

	while x != 1 {
		count = count + 1

		// Divide by 2 when even
		if x % 2 == 0 {
			x = x / 2

			if show {
				println(x)
			}
		} else {
			// Multiply by 3 and add 1 when odd
			x = (3 * x) + 1

			if show {
				println(x)
			}
		}
	}

	return count
}

// Main method
func main() => void {
	num limit = 40
	num maxCount = 0
	num maxIndex = 0

	// Find the longest sequence that eventually reduces to 1
	for num x in range(1, limit + 1) {
		num count = collatz(x, false)
		println("(" + x + ") " + count)

		if count > maxCount {
			maxCount = count
			maxIndex = x
		}
	}

	println("Max iterations = " + maxCount + " at number " + maxIndex)
}
