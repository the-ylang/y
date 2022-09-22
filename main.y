use stdio;
use os as "";

/*
    Multiple command line
*/

// Single comment line

void fn invert(udf .nb1, udf .nb2){
    udf temp;
    temp = .nb1;
    .nb1 = .nb2;
    .nb2 = temp;
}

int number1 = 12;
int number2 = 65;

udf var1 = 'Y';
udf var2 = "Y is the best programming language !";

stdio.out(number1, number2);
invert(&number1, &number2);
stdio.out(number1, number2);

stdio.out(get_device_name()) # os.get_device_name()

stdio.out(var1, var2);
invert(&var1, &var1);
stdio.out(var1, var2);
