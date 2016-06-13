#include "Cell.h"
Cell::Cell(Color color) : color(color) {
}
void Cell::print_color() const {
	std::cout << color << std::endl;
	return;
}

void f() {
	Cell c(Red);
	c.print_color();
	return;	
}
