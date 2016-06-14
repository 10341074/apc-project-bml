#include "Cell.h"
Cell::Cell(Color color) : color(color) {
}
void Cell::update_u(Cell * p) {
	nbhd.cell_u=p;
	return;
}
void Cell::update_d(Cell * p) {
	nbhd.cell_u=p;
	return;
}
void Cell::update_l(Cell * p) {
	nbhd.cell_u=p;
	return;
}
void Cell::update_r(Cell * p) {
	nbhd.cell_u=p;
	return;
}
Color & Cell::get_color() {
	return color;
}
const Color & Cell::get_color() const {
	return color;
}
Cell * Cell::get_u() {
	return nbhd.cell_u;
}
Cell * Cell::get_d() {
	return nbhd.cell_d;
}
Cell * Cell::get_l() {
	return nbhd.cell_l;
}
Cell * Cell::get_r() {
	return nbhd.cell_r;
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
std::ostream & operator<<(std::ostream & os, const Cell & c) {
	os << c.color;
	return os;
};
