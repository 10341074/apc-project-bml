#ifndef COLUMN_IT_H
#define COLUMN_IT_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>

#include "Color.h"

class Const_ScalarPointer { // non-const pointer to const Scalar // no memory menagement: no new - no delete
  private:
    std::vector< Scalar >::const_iterator scalar_p_;
  public:
    Const_ScalarPointer()                                           = default;
    ~Const_ScalarPointer() {}                                       // no deallocation
    Const_ScalarPointer(const Const_ScalarPointer & s)              = default;
    Const_ScalarPointer & operator=(const Const_ScalarPointer & s) 	= default;
    Const_ScalarPointer(Const_ScalarPointer && s)                   = default;
    Const_ScalarPointer & operator=(Const_ScalarPointer && s)       = default;

    Const_ScalarPointer(const std::vector< Scalar >::const_iterator & it) :   scalar_p_(it) {}
    Const_ScalarPointer(std::vector< Scalar >::const_iterator && it) :        scalar_p_(it) {}
    
    Const_ScalarPointer & operator++();
};

class Const_ColumnIt { // non-const column to const Scalar
  protected:
//  std::vector< Const_ScalarPointer > column_;
    std::vector< std::vector< Scalar>::const_iterator > column_;

  public:
    Const_ColumnIt()    = delete; 
    ~Const_ColumnIt()   = default;
    Const_ColumnIt(const std::list< std::vector< Scalar > > & m_inp);
    
    Const_ColumnIt & operator++();

    std::vector< std::vector< Scalar>::const_iterator  >::const_iterator begin()    { return column_.begin(); }
    std::vector< std::vector< Scalar>::const_iterator  >::const_iterator end()      { return column_.end(); }

    struct const_iterator {
      private:
        std::vector< std::vector< Scalar>::const_iterator >::const_iterator iterator;
      public:
        const_iterator(const std::vector< std::vector< Scalar>::const_iterator >::const_iterator & it);
        const_iterator & operator=(const std::vector< std::vector< Scalar>::const_iterator >::const_iterator & it);
        const_iterator & operator=(std::vector< std::vector< Scalar>::const_iterator >::const_iterator && it);
        const Scalar & operator*()    { return **iterator; }
        const_iterator & operator++() { ++iterator; return * this; }
        bool operator!=(const std::vector< std::vector< Scalar>::const_iterator >::const_iterator & it) { return iterator != it; }
    };
};
  

#endif
