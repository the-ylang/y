use stdio

/*
    Comment lines
*/
// Comment line
const str helloPeople << ["Hello, World!", "Bye, World!"];

foreach (i, helloPeople) {
    stdio.out << i;
}

int add(int a, int b) {
    return a + b;
}

use stdio as ""
foreach (i, helloPeople) {
    out << i;
}
add(5, 36);