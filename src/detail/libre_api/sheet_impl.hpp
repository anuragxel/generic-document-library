#ifndef _LIBRE_SHEET_IMPL_HPP
#define _LIBRE_SHEET_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <memory>

#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/sheet_interface.hpp>

#include <boost/document/detail/libre_api/libre_sheet_func.hpp>

namespace boost { namespace detail { 

class libre_sheet: public sheet_interface {
	private:
	::com::sun::star::uno::Reference < com::sun::star::lang::XComponent > xComponent_;
	::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet > XSpreadsheet_;
	int index;
	std::string name;
	public:
	libre_sheet(::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& XSpreadsheet, int& index) {
		this->xComponent_ = xComponent;
		this->XSpreadsheet_ = XSpreadsheet;
		this->index = index;
		this->name = this->sheet_name();
	}

	libre_sheet(::com::sun::star::uno::Reference < com::sun::star::lang::XComponent >& xComponent,
		::com::sun::star::uno::Reference< com::sun::star::sheet::XSpreadsheet >& XSpreadsheet, std::string& str) {
		this->xComponent_ = xComponent;
		this->XSpreadsheet_ = XSpreadsheet;
		this->index = this->sheet_index();
		this->name = str;
	}

	std::string sheet_name() {
		return "sheet";
	}

	int sheet_index() {
		return 1;
	}

	void remame_sheet(const std::string& str) {
	 	
	}

 	~libre_sheet() {
 		
 	}

};

}} // namespace boost::detail


#endif
