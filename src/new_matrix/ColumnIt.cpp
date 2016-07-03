#include "ColumnIt.h"

Const_ScalarPointer & Const_ScalarPointer::operator++() {
  ++scalar_p_;
  return * this; 
}

Const_ColumnIt::Const_ColumnIt(const std::list< std::vector< Scalar > > & m_inp) : column_(std::vector< std::vector< Scalar>::const_iterator >(m_inp.size())) {
  if(m_inp.empty())
    throw std::runtime_error("Const_ColumnIt constructor: empty list");

  std::list< std::vector< Scalar> >::const_iterator it_from = m_inp.begin();
  for(std::vector< std::vector< Scalar>::const_iterator >::iterator it_to = column_.begin(); it_to != column_.end(); ++it_to) {
    if(it_from->size() == 0)
      throw std::runtime_error("Const_ColumnIt constructos: list of empty vectors");
    * it_to = (* it_from).begin();
    ++it_from;
  }
}
Const_ColumnIt & Const_ColumnIt::operator++() {
  for(std::vector< std::vector< Scalar>::const_iterator >::iterator it = column_.begin(); it != column_.end(); ++it) {
     ++ (* it);
  }
  return * this;
}
Const_ColumnIt::const_iterator::const_iterator(const std::vector< std::vector< Scalar>::const_iterator >::const_iterator & it) : iterator(it) {}
Const_ColumnIt::const_iterator & Const_ColumnIt::const_iterator::operator=(const std::vector< std::vector< Scalar>::const_iterator >::const_iterator & it) {
  iterator = it;
  return * this;
}
Const_ColumnIt::const_iterator & Const_ColumnIt::const_iterator::operator=(std::vector< std::vector< Scalar>::const_iterator >::const_iterator && it) {
  iterator = it;
  return * this;
}


