#ifndef _DOCUMENT_HPP
#define _DOCUMENT_HPP

//          Copyright Anurag Ghosh 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file ../../../../../LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <memory>
#include <boost/filesystem.hpp>


#include <boost/document/detail/document_exception.hpp>
#include <boost/document/detail/document_file_format.hpp>
#include <boost/document/detail/document_interface.hpp>

#include <boost/document/sheet.hpp>


namespace boost {

	 namespace detail {
		std::shared_ptr<document_interface> open_instance();
	}
    //! \brief This is the main class interface to be 
    //!        exposed to the library user.
    //!
	class document {
	private:
		std::shared_ptr<document_interface> pimpl_;
		std::shared_ptr<document_interface> init() {
 	   		return boost::detail::open_instance();
		}
	public:
		//! \brief The Constructor.
		//!        Creates a new document object.  
		document(const boost::filesystem::path& path) : pimpl_(init()) {
			pimpl_->initialize(path);
		}
		//! \brief creates document using Calc/Excel given in
		//!        the file path.
		void create_document() {
			pimpl_->create();
		}
		//! \brief Opens document using Calc/Excel given in
		//!        the file path.
		void open_document() {
			pimpl_->open();
		}
		//! \brief Closes document using Calc/Excel given in
		//!        the file path.
		void close_document() {
			pimpl_->close();
		}
		//! \brief saves document using Calc/Excel given in
		//!        the file path.
		void save_document() {
			pimpl_->save();
		}

		//! \brief saves document at the path using Calc/Excel provided in
		//!        first argument.
		void save_as_document(const boost::filesystem::path& path) {
			pimpl_->save_as(path);
		}

		//! \brief Exports document using Calc/Excel given in
		//!        the file path and the file format. Default
		//!        format is PDF.
		void export_document(boost::document_file_format::type format = document_file_format::PDF) {
			pimpl_->export_as(format);
		}

		//! \brief Gets a sheet instance of name str
		//!        which can be manipulated as needed.
		boost::sheet get_sheet(const std::string& str) {
			return pimpl_->get_sheet(str);
		}
		
		//! \brief Gets a sheet instance of that index
		//!        which can be manipulated as needed.
		boost::sheet get_sheet(int index) {
			return pimpl_->get_sheet(index);
		}

		//! \brief Deletes the sheet of name str
		void delete_sheet(const std::string& str) {
			pimpl_->delete_sheet(str);
		}

		//! \brief Deletes the sheet of name str
		void delete_sheet(int index) {
			pimpl_->delete_sheet(index);
		}

		int sheet_count() {
			return pimpl_->sheet_count();
		}
		//! \brief Destructor
		//!        Closes Unsaved Documents.
		~document() {
		}
		
	};
} // namespace boost

#endif
