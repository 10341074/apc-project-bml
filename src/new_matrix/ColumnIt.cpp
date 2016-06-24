#include "ColumnIt.h"

Const_ScalarPointer & Const_ScalarPointer::operator++() {
  ++scalar_p_;
  return * this; 
}
Const_ColumnIt::Const_ColumnIt(const std::list< std::vector< Scalar > > & m_inp) : column_(std::vector< std::vector< Scalar>::const_iterator >(m_inp.size())) {
  std::list< std::vector< Scalar> >::const_iterator it_from = m_inp.begin();
  for(std::vector< std::vector< Scalar>::const_iterator >::iterator it_to = column_.begin(); it_to != column_.end(); ++it_to) {
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
void f() {
  std::vector< std::vector< Scalar>::const_iterator > column_;
  const std::vector< std::vector< Scalar>::const_iterator >::const_iterator ii = column_.begin();
  Const_ColumnIt::const_iterator i(ii );
}



