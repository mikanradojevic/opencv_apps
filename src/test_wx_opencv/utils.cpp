#include "utils.h"
#include "wx/log.h"

std::string wxstr_to_std(const wxString& str)
{
	std::string std_str(str.mb_str());
	return std_str;
}

wxString stdstr_to_wx(const std::string& str)
{
	return wxString(str.c_str(), wxConvUTF8); 
}

//////////////////////////////////////////////////////////////////////////

void wx_log_fatal(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	wxVLogFatalError(wxString(str, wxConvUTF8).c_str(), args);
	va_end(args);
}

void wx_log_error(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	fprintf(stderr, "\n");
	wxVLogError(wxString(str, wxConvUTF8).c_str(), args);
	va_end(args);
}

void wx_log_warning(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	fprintf(stderr, "\n");
	wxVLogWarning(wxString(str, wxConvUTF8).c_str(), args);
	va_end(args); 
}

void wx_log_message(const char *str, ...)
{
	va_list args;
	va_start(args, str);
	vfprintf(stderr, str, args);
	fprintf(stderr, "\n");
	wxVLogMessage(wxString(str, wxConvUTF8).c_str(), args);
	va_end(args);
}