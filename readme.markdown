# Deduction

Deduction is a library and command line application that parses C and C++ header files and creates a JSON description from them.  This description exposes details about the public types that can be easily consumed by other tooling.

It is primarily intended as part of a trio of projects that intend to make it easier to share code written in C++ by generating bindings for other languages.

## Example

Consider a header file with the following information:

	namespace examplelib {
		extern std::string const version_info;
	
		struct core {
			core() = default;
			void do_something() const;
		};
	}

It will produce a description similar to:

	"items": [
		{
			"_type": "variable",
			"is_extern": true,
			"is_mutable": false,
			"name": "version_info",
			"type": "const std::string",
			"type_without_qualifiers": "std::string"
		},
		{
			"_type": "struct",
			"constructors": [
				{
					"full_name": "examplelib::core::core",
					"name": "core",
					"parameters": []
				}
			],
			"fields": [],
			"full_name": "examplelib::core",
			"methods": [
				{
					"full_name": "examplelib::core::do_something",
					"name": "do_something",
					"parameters": [],
					"return_type": "void"
				}
			],
			"name": "core"
		}
	]

## Why?!

Many teams and projects could benefit from sharing code across multiple platforms.  Unfortunately, many of the cross-platform solutions have short-coming.  Many only target specific platforms (frequently iOS/Android-only).  Others introduce significant costs in terms of performance, resource usage, or simply having to compile an extensive runtime and standard library into every application.  Many solutions don't provide adequate debugging stories.  C and C++ continue to be the primary languages that provide the best support for precise resource management, compiling to multiple targets, and well-developed tooling.

The de facto standard for communicating across language barriers continues to be C.	 C ABIs are well-documented and simple enough to be readily bridged into nearly all major platform languages.  Unfortunately, C libraries tend to be very low-level or rely on hacks like preprocessor macros to provide full-featured APIs that support multiple data types.  C++ provides plenty of power for common application APIs, has a reasonable standard API (programmers from languages like C# or Python may consider it lacking), and has access to a deep library of C and C++ support libraries.  On nearly every platform, there are no additional library or runtime requirements for running bare C/C++ applications and the debugging story is pretty well defined with some pretty good tooling.

C libraries represent the best interoperability story and C++ libraries have a superior standard library and more powerful idioms.  If we could program in C++ but have C's ubiquity, we could leverage the best parts of both languages.  Common integration stories often involve utilizing language bridges to define C/C++ code in a file and generating the bindings for each native platform.  Other solutions involve committing to authoring a C wrapper library around a C++ codebase.

This project is part of a trio of projects that explores the possibility of automatically generating language bindings from a C++ project.

`deduction` is the puzzle piece that begins abstracting the original, core library.	 It reads C and C++ header files and converts them into JSON descriptions.	These are general, all-purpose name-and-type descriptions of the internal API.	They aren't interesting except that they provide *just enough* information to do other interesting things (like define a C wrapper API).  `deduction` is not intended to provide a complete description of all potential C/C++ types.  Instead, it will focus on a limited, but useful, subset of C and C++ features (macro support is right out).

It is the expectation of this project that, with a reasonable subset of common data types supported, many C/C++ libraries can expose a limited public API that is parseable by `deduction`.  These parsed descriptions can be converted into language bindings automatically through other tooling.

## Contact info

[Grayson Hansard](grayson.hansard@gmail.com)  
[@Grayson](http://twitter.com/Grayson)
