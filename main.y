use stdio;

/*
	Multiline comment
*/
// Singleline comment

fn int add(int num, int sec_num) {
	return num + sec_num;
}

fn void invert(mut var, mut var_sec) {
	let mut temp;
	temp << var;
	var << var_sec;
	var_sec << temp;
}

fn main(str[] args) {
	// Declarations
	let int number1 << 12;
	let int number2 << 21;
	let int sum << add(number1, number2);
	let mut var1 << true;
	let mut var2 << "The Y Programming Language";

	// First output
	outln("{number1} + {number2} << {sum}"); // stdio.outln(); if use stdio.outln();
	// Invert variables + outputs
	outln("{var1} - {var2}");
	invert(.var1, .var2);
	outln("{var1} - {var2}");
}
