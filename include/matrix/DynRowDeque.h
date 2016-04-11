#ifndef DYNROWDEQUE_H
#define DYNROWDEQUE_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <deque>
#include <memory>

#include "Template.h"
#include "Color.h"
#include "Row.h"
#include "Car.h"

using DequeCar = std::deque<Car>;

class DynRowDeque{
	DequeCar * row = nullptr;
	std::size_t length = 0;
	public:
	DynRowDeque();
	~DynRowDeque();
	DynRowDeque(const DynRowDeque & dr);
	DynRowDeque & operator=(const DynRowDeque & dr);
	DynRowDeque(DynRowDeque && dr);
	DynRowDeque & operator=(DynRowDeque && dr);
	
//	danger: memory is owned by external
	DynRowDeque(DequeCar * & r, size_type l);
	DynRowDeque(std::unique_ptr<DequeCar> r, size_type l);
//	DynRowDeque(size_type s);
	
	size_type size() const;
	bool empty() const;
	
	DequeCar::iterator begin();
	DequeCar::const_iterator begin() const;
//	DequeCar::const_iterator cbegin() const;
	DequeCar::iterator end();
	DequeCar::const_iterator end() const;
//	DequeCar::const_iterator cend() const;
	
	void push_back(const Car & car);
	void push_back(Car && car);
	const DequeCar * const get_row_pointer() const { return row; }
	void move(const Color & cl);
};
#endif
