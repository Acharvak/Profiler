#ifndef OCRC_DOCXMLWRITER_CXX
#define OCRC_DOCXMLWRITER_CXX OCRC_DOCXMLWRITER_CXX

#include "./DocXMLWriter.h"
#include "Utils/NoThousandGrouping.h"

namespace OCRCorrection {
    void DocXMLWriter::writeXML( Document const& doc, std::wostream& xml_out ) const {

	xml_out.imbue(std::locale(std::locale(), new NoThousandGroupingWithDecimalDot()));

	// at least try to make sure that the wostream is imbued with a decent locale
	if( ! ( std::use_facet< std::numpunct< wchar_t > >( xml_out.getloc() ).decimal_point() == '.' ) ) {
	    throw OCRCException("OCRC::DocXMLWriter::writeXML: The specified wostream "
				"object uses a locale which does not use '.' as decimal point." );
	}

	xml_out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
		<< "<document>" << std::endl
	    ;

	size_t tokenCount = 0;
	writeAdaptiveTokens(doc, xml_out);
	if( ! doc.hasPages() ) {
		writeTokens(doc.begin(), doc.end(), tokenCount, xml_out);
	} else {
		writePages(doc.pagesBegin(), doc.pagesEnd(), tokenCount, xml_out);
	}
	xml_out << "</document>" << std::endl;
    }
    void DocXMLWriter::writePages(PageIterator b, PageIterator e, size_t& tokenCount, std::wostream& xml_out) const {
	    for (auto pageIt = b; pageIt != e; ++pageIt) {
		    xml_out << "<page imageFile=\"" << Utils::utf8(pageIt->getImageFile()) /*csl::CSLLocale::string2wstring( pageIt->getImageFile() )*/ << "\" sourceFile=\"" << Utils::utf8(pageIt->getSourceFile()) /*csl::CSLLocale::string2wstring( pageIt->getSourceFile() )*/<< "\">" <<std::endl;
			writeTokens(pageIt->begin(), pageIt->end(), tokenCount, xml_out);
		    xml_out << "</page>" << std::endl;
	    }
    }

    void DocXMLWriter::writeTokens(TokenIterator b, TokenIterator e, size_t& tokenCount, std::wostream& xml_out) const {
	    for( Document::const_iterator token = b; token != e; ++token ) {
		if( token->getWOCR() == L" " ) {
		    xml_out
			<< "<token token_id=\"" << tokenCount << "\" special_seq=\"space\" isNormal=\"false\">" << std::endl
		        << "<ext_id>" << token->getExternalId() << "</ext_id>" << std::endl
			<<  "<wOCR>" << xml_escape( token->getWOCR() ) << "</wOCR>" << std::endl
			<<  "<wOCR_lc>" << xml_escape( token->getWOCR_lc() ) << "</wOCR_lc>" << std::endl
			<<  "<wCorr>" << xml_escape( token->getWCorr() ) << "</wCorr>" << std::endl;

		    if( token->hasGroundtruth() ) {
			xml_out
			    << "<groundtruth verified=\"false\">" << std::endl
			    << "<classified>" << xml_escape( token->getGroundtruth().getClassified() ) << "</classified>" << std::endl
			    << "<wOrig>" << xml_escape( token->getGroundtruth().getWOrig() ) << "</wOrig>" << std::endl
			    << "<wOrig_lc>" << xml_escape( token->getGroundtruth().getWOrig_lc() ) << "</wOrig_lc>" << std::endl
			    << "</groundtruth>" << std::endl;
		    }
		    xml_out
			<< "</token>" << std::endl;
		}
		else if( token->getWOCR() == L"\n" ) {
		    xml_out
			<< "<token token_id=\"" << tokenCount << "\" special_seq=\"newline\" isNormal=\"false\">" << std::endl
		        << "<ext_id>" << token->getExternalId() << "</ext_id>" << std::endl
			<< "<wOCR>" << xml_escape( token->getWOCR() )<< "</wOCR>" << std::endl
			<< "<wOCR_lc>" << xml_escape( token->getWOCR_lc() ) << "</wOCR_lc>" << std::endl
			<< "<wCorr>" << xml_escape( token->getWCorr() ) << "</wCorr>" << std::endl;

		    if( token->hasGroundtruth() ) {
			xml_out
			    << "<groundtruth verified=\"false\">" << std::endl
			    << " <classified>" << xml_escape( token->getGroundtruth().getClassified() ) << "</classified>" << std::endl
			    << " <wOrig>" << xml_escape( token->getGroundtruth().getWOrig() ) << "</wOrig>" << std::endl
			    << " <wOrig_lc>" << xml_escape( token->getGroundtruth().getWOrig_lc() ) << "</wOrig_lc>" << std::endl
			    << "</groundtruth>" << std::endl;
		    }
		    xml_out	<< "</token>" << std::endl;
		}
		else {
		    std::wstring isNormal_string = (token->isNormal() )? L"true" : L"false";
		    xml_out
			<< "<token token_id=\"" << tokenCount << "\" isNormal=\""<< isNormal_string << "\">" << std::endl
		        << "<ext_id>" << token->getExternalId() << "</ext_id>" << std::endl
			<< "<wOCR>" << xml_escape( token->getWOCR() ) << "</wOCR>" << std::endl
			<< "<wOCR_lc>" << xml_escape( token->getWOCR_lc() ) << "</wOCR_lc>" << std::endl;
		    	if (token->has_metadata("correction")) {
				xml_out << "<wCorr>"
					<< xml_escape(token->metadata()["correction"])
					<< "</wCorr>" << std::endl;
			}


		    for( Token::CandidateIterator cand = token->candidatesBegin();
			 cand != token->candidatesEnd();
                 ++cand ) {
                    std::wostringstream os;
                    // use same locale for stringstream as for xml stream
                    os.imbue(xml_out.getloc());
                    cand->print(os);
			xml_out
			    <<  "<cand>"
			    << xml_escape(os.str())
			    << "</cand>" << std::endl;
		    }

		    if( token->getTokenImageInfoBox() ) {
			xml_out
			    << "<coord l=\"" << token->getTokenImageInfoBox()->getCoordinate_Left() << "\""
			    << " t=\"" << token->getTokenImageInfoBox()->getCoordinate_Top() << "\""
			    << " r=\"" << token->getTokenImageInfoBox()->getCoordinate_Right() << "\""
			    << " b=\"" << token->getTokenImageInfoBox()->getCoordinate_Bottom() << "\""
			    << "/>"
			    << std::endl;
		    }

		    xml_out
			<< "<abbyy_suspicious value=\"" << ( token->getAbbyySpecifics().isSuspicious() ? L"true" : L"false" ) << "\"/>" << std::endl;

		    if( token->hasGroundtruth() ) {
			xml_out
			    << "<groundtruth verified=\"" << ( (token->getGroundtruth().getVerified())? L"true" : L"false" ) << "\">" << std::endl
			    << " <classified>" << xml_escape( token->getGroundtruth().getClassified() ) << "</classified>" << std::endl
			    << " <wOrig>" << xml_escape( token->getGroundtruth().getWOrig() ) << "</wOrig>" << std::endl
			    << " <wOrig_lc>" << xml_escape( token->getGroundtruth().getWOrig_lc() ) << "</wOrig_lc>" << std::endl
			    << " <baseWord>" << xml_escape( token->getGroundtruth().getBaseWord() ) << "</baseWord>" << std::endl
			    << " <histTrace>" << xml_escape( token->getGroundtruth().getHistTrace() ) << "</histTrace>" << std::endl
			    << " <ocrTrace>" << xml_escape( token->getGroundtruth().getOCRTrace() ) << "</ocrTrace>" << std::endl
			    << "</groundtruth>" << std::endl;
		    }
		    xml_out
			<< "</token>" << std::endl;
		}
		++tokenCount;
	} // for all tokens
    }


    void DocXMLWriter::writeXML( Document const& doc, std::string const& filename ) const {
	std::wofstream of( filename.c_str() );
	//of.imbue( csl::CSLLocale::Instance() );
	if( ! of.good() ) {
	    throw OCRCException( "OCRC::DocXMLWriter::writeXML: Could not open file for writing" );
	}
	DocXMLWriter writer;
	writer.writeXML( doc, of );
	std::wcerr << "OCRC::DocXMLWriter::writeXML: xml written" << std::endl;

	of.close();
    }

    void DocXMLWriter::writeAdaptiveTokens(const Document& doc, std::wostream& xml_out) const {
	xml_out << "<adaptiveTokens>\n";
	for (const auto& token: doc.getAdaptiveTokens()) {
		xml_out << "<adaptiveToken>" << xml_escape(token) << "</adaptiveToken>\n";
	}
	xml_out << "</adaptiveTokens>\n";
    }


}
#endif
