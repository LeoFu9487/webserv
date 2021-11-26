#pragma once
#include "webserv.hpp"

typedef enum
{
	Continue = 100,
	SwitchingProtocols,
	Processing,
	EarlyHints,
	OK = 200,
	Created,
	Accepted,
	Non_AuthoritativeInformation,
	NoContent,
	ResetContent,
	PartialContent,
	Multi_Status,
	AlreadyReported,
	IMUsed = 226,
	MultipleChoices = 300,
	MovedPermanently,
	Found,
	SeeOther,
	NotModified,
	UseProxy,
	SwitchProxy,
	TemporaryRedirect,
	PermanentRedirect,
	BadRequest = 400,
	Unauthorized,
	PaymentRequired,
	Forbidden,
	NotFound,
	MethodNotAllowed,
	NotAcceptable,
	ProxyAuthenticationRequired,
	RequestTimeout,
	Conflict,
	Gone,
	LengthRequired,
	PreconditionFailed,
	PayloadTooLarge,
	URITooLong,
	UnsupportedMediaType,
	RangeNotSatisfiable,
	ExpectationFailed,
	ImATeapot,
	MisdirectedRequest = 421,
	UnprocessableEntity,
	Locked,
	FailedDependency,
	TooEarly,
	UpgradeRequired,
	PreconditionRequired = 428,
	TooManyRequests,
	RequestHeaderFiledsTooLarge = 431,
	UnavailableForLegalReasons = 451,
	InternalServerError = 500,
	NotImplemented,
	BadGateway,
	ServiceUnavailable,
	GatewayTimeout,
	HTTPVersionNotSupported,
	VariantAlsoNegotiates,
	InsufficientStorage,
	LoopDetected,
	NotExtended = 510,
	NetworkAuthenticationRequired
} status_code;

class HTTPResponse
{
	private:
		static std::map<int, std::string> init_map()
		{
			std::map<int, std::string> status;
			status[100] = "Continue";
			status[101] = "Switching Protocols";
			status[102] = "Processing";
			status[103] = "Early Hints";
			status[200] = "OK";
			status[201] = "Created";
			status[202] = "Accepted";
			status[203] = "Non-Authoritative Information";
			status[204] = "No Content";
			status[205] = "Reset Content";
			status[206] = "Partial Content";
			status[207] = "Multi-Status";
			status[208] = "Already Reported";
			status[226] = "IM Used";
			status[300] = "Multiple Choices";
			status[301] = "Moved Permanently";
			status[302] = "Found";
			status[303] = "See Other";
			status[304] = "Not Modified";
			status[305] = "Use Proxy";
			status[306] = "Switch Proxy";
			status[307] = "Temporary Redirect";
			status[308] = "Permanent Redirect";
			status[400] = "Bad Request";
			status[401] = "Unauthorized";
			status[402] = "Payment Required";
			status[403] = "Forbidden";
			status[404] = "Not Found";
			status[405] = "Method Not Allowed";
			status[406] = "Not Acceptable";
			status[407] = "Proxy Authentication Required";
			status[408] = "Request Timeout";
			status[409] = "Conflict";
			status[410] = "Gone";
			status[411] = "Length Required";
			status[412] = "Precondition Failed";
			status[413] = "Payload Too Large";
			status[414] = "URI Too Long";
			status[415] = "Unsupported Media Type";
			status[416] = "Range Not Satisfiable";
			status[417] = "Expectation Failed";
			status[418] = "I\'m a teapot"; 
			status[421] = "Misdirected Request";
			status[422] = "Unprocessable Entity";
			status[423] = "Locked";
			status[424] = "Failed Dependency";
			status[425] = "Too Early";
			status[426] = "Upgrade Required";
			status[428] = "Precondition Required";
			status[429] = "Too Many Requests";
			status[431] = "Request Header Fields Too Large";
			status[451] = "Unavailable For Legal Reasons";
			status[500] = "Internal Server Error";
			status[501] = "Not Implemented";
			status[502] = "Bad Gateway";
			status[503] = "Service Unavailable";
			status[504] = "Gateway Timeout";
			status[505] = "HTTP Version Not Supported";
			status[506] = "Variant Also Negotiates";
			status[507] = "Insufficient Storage";
			status[508] = "Loop Detected";
			status[510] = "Not Extended";
			status[511] = "Network Authentication Required";

			return status;
		}
		static std::map<int, std::string> _status_line;
	public:
		

};


/*
source : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
*/

