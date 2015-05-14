#ifndef _MS_DOCUMENT_IMPL_HPP
#define _MS_DOCUMENT_IMPL_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <windows.h>
#include <ole2.h>

#include <boost/filesystem.hpp>
#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_interface.hpp>
#include <boost/document/detail/ms_api/ms_functions.hpp>

namespace boost { namespace detail { 

class ms_document: public document_interface {
	
	boost::filesystem::path doc_path_;
	bool is_file_opened;	
	CLSID clsid_;
	IDispatch *appl_ptr_;

	void initialize(const boost::filesystem::path& fpath) {
		CoInitialize(NULL);
		this->doc_path_ = fpath;
		if(!boost::filesystem::exists(this->doc_path_)) {
        		boost::throw_exception(document_exception(
            		"Error: Path is empty or does not exist."));
    		}
		this->clsid = boost::doc::ms_functions::get_clsid();
		this->appl_ptr_ = boost::doc::ms_functions::get_application_pointer(clsid);
		this->is_file_opened = false;
	}

	void open() {
		if(!this->is_file_opened) {
			boost::doc::ms_functions::open_ms(this->doc_path_,this->appl_ptr_);
			this->is_file_opened = true;
		}
 	}

 	void close() {
 		if(this->is_file_opened) {
			boost::doc::ms_functions::close_ms(this->doc_path_, false, this->appl_ptr_);
			this->is_file_opened = false;
		}
		else {
			boost::throw_exception(document_exception(
            		"Error: Trying to close unopened file."));	
		}
 	}
 	
 	void save() {
 		if(!this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
 		boost::doc::ms_functions::save_ms(this->doc_path_, this->appl_ptr_);
 	}
 	
 	void save_as(const boost::filesystem::path& fpath) {
 		if(! this->is_file_opened) {
			boost::throw_exception(document_exception(
            		"Error: Trying to save unopened file."));
		}
 		//boost::doc::libre_functions::save_libre(fpath, this->xComponent_);
 	}
 	
 	void export_as(boost::document_file_format::type format) {
 		if(! this->is_file_opened) {
 			boost::throw_exception(document_exception(
            		"Error: Trying to export unopened file."));
 		}
 		boost::doc::ms_functions::export_ms(this->doc_path_, format, this->appl_ptr_);
 	}

 	~ms_document() {
 		if(this->is_file_opened) {
			boost::doc::ms_functions::close_ms(this->doc_path_, false, this->appl_ptr_);
			this->is_file_opened = false;
		}
		CoUninitialize(NULL);

 	}

};

document_interface* open_ms_instance() {
	return new ms_document();
}

}} // namespace boost::detail


#endif