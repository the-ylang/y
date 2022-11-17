use stdio;

/*
	Multiline comment
*/
// Singleline comment

fn int add(int num, int sec_num) {
	return num + sec_num;
}

fn void invert(udf var, udf var_sec) {
	udf temp;
	temp = var;
	var = var_sec;
	var_sec = temp;
}

fn main(str[] args) {
	// Declarations
	int number1 = 12;
	int number2 = 21;
	int sum = add(number1, number2);
	udf var1 = true;
	udf var2 = "The Y Programming Language";

	// First output
	outln("{number1} + {number2} = {sum}"); // stdio.outln(); if use stdio.outln();
	// Invert variables + outputs
	outln("{var1} - {var2}");
	invert(.var1, .var2);
	outln("{var1} - {var2}");
}
