//////////////////////////////////////////////////////////////////////////
//  Copyright (c) 2009-2012 Organic Vectory B.V.
//  Written by George van Venrooij
//
//  Contributions by:   
//      Fredrik Orderud (https://sourceforge.net/users/fredrior/)
//      Ian Cullinan    (https://sourceforge.net/users/cibyr/)
//
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file license.txt)
//////////////////////////////////////////////////////////////////////////

//! \mainpage CLCC - The OpenCL kernel Compiler
//!
//! SourceForge.net project page:   http://www.sourceforge.net/projects/clcc
//!
//! \ref Introduction   \n
//! \ref Benefits       \n
//! \ref Usage          \n
//! \ref License        \n
//! \ref Building       \n
//! \ref Compatibility  \n
//! \ref Changelog      \n
//! \ref Todo List      \n
//! \ref Credits        \n
//!
//! \section Introduction
//! 
//! CLCC is a compiler for OpenCL kernel source files. It is intended to
//! be a tool for application developers who need to incorporate OpenCL
//! source code into their programs and who want to verify their OpenCL
//! code actually gets compiled by the driver before their program tries
//! to compile it on-demand.
//!
//! \section Benefits
//!
//! The benefits of using CLCC are simple: when building an OpenCL
//! application, you write "normal" code and OpenCL code. The normal code
//! gets checked by your ordinary compiler, but the OpenCL code is not,
//! leaving you with the task of handling compilation errors in your
//! application code. Something which isn't always possible or easy.
//!
//! By compiling your code with CLCC during the build phase, you can quickly
//! spot errors and fix them in your favorite development environment.
//!
//! \section Usage
//!
//! CLCC can be invoked from the command-line using the following syntax:
//!
//! - \b clcc [%options] file(s)...
//!
//! Options are:
//! - \b --help show the list of available %options
//! - \b --version display the version number of the program
//! - \b --info display a list of OpenCL platforms and devices
//! - \b --cloptions options to pass to the OpenCL compiler
//! - \b --clpath \e &lt;arg&gt; specify which OpenCL dynamic library to load
//! - \b --platform_filter case-insensitive platform name filter
//! - \b --device_filter case-insensitive device name filter
//! - \b --device_type \e &lt;arg&gt; specify which device type to compile for,
//! where \e &lt;arg&gt; can be one of:
//!   - \b CPU compile for CPU devices
//!   - \b GPU compile for GPU devices
//!   - \b ACCELERATOR compile for ACCELERATOR devices
//!   - \b ALL compile for all devices (\e default) 
//! - \b --platform_index,-p zero-based index of platform to compile for
//! - \b --device_index,-d zero-based index of device to compiler for
//! - \b --add_headers add CLCC headers to output binaries
//! 
//! If you specify more than on OpenCL source file on the command line, the
//! files are compiled into a single program. \b Note that this behavior 
//! differs from the behavior in version 0.1
//! 
//! \section License
//! 
//! This project is available under the Boost Software License, Version 1.0
//!
//! Permission is hereby granted, free of charge, to any person or organization
//! obtaining a copy of the software and accompanying documentation covered by
//! this license (the "Software") to use, reproduce, display, distribute,
//! execute, and transmit the Software, and to prepare derivative works of the
//! Software, and to permit third-parties to whom the Software is furnished to
//! do so, all subject to the following:
//! 
//! The copyright notices in the Software and this entire statement, including
//! the above license grant, this restriction and the following disclaimer,
//! must be included in all copies of the Software, in whole or in part, and
//! all derivative works of the Software, unless such copies or derivative
//! works are solely in the form of machine-executable object code generated by
//! a source language processor.
//! 
//! THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//! IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//! FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
//! SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
//! FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
//! ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
//! DEALINGS IN THE SOFTWARE.
//!
//! \section Building
//!
//! To build CLCC you will need to have a copy of the Boost Libraries
//! installed on your system. You will find these at http://www.boost.org
//! This version was built against Boost version 1.47.0
//!
//! To generate makefiles and/or project files for your favorite IDE on your
//! favorite platform, you will need CMake version 2.8 or higher, which you can 
//! find at http://www.cmake.org 
//! 
//! Parts of this code are  Copyright (c) 2008-2009 The Khronos Group Inc.
//! Find more information on OpenCL at http://www.khronos.org/opencl/
//!
//! To build CLCC from source, follow these steps:
//!
//!	- Unpack the source code into a folder (i.e. \b clcc)
//! - Create a build directory (i.e. \b build)
//! - From within the build folder, execute CMake to configure the project.
//!   Don't forget to specify the Boost root folder on the command-line in
//!	  case it cannot be found automatically by CMake: 
//!   - <b>cmake -DBOOST_ROOT=<path_to_your_boost> <path_to_clcc_source_dir></b>
//!	-	To build clcc itself run 
//!	  - <b>cmake --build . --config Release --target clcc</b>
//!	- To build the documentation run 
//!	  - <b>cmake --build . --config Release --target clcc_doc</b>
//!	- To build an installer package run
//!	  - <b>cmake --build . --config Release --target package</b>
//!
//! \section Compatibility
//!
//! This code was built and tested on the following platforms:
//!
//! - Windows XP (x64, SP2) using Visual Studio 2008 (SP1)
//! - Max OS X 10.6.2 using XCode 3.2.1
//! 
//! The code should compile on any decent C++ compiler, but your mileage may vary.
//!
//! \subsection Running
//!
//! To run CLCC on any platform you will need a properly installed OpenCL driver.
//! CLCC will attempt to locate the OpenCL dynamic library automatically, but if
//! it fails you can try to pass it to CLCC by using the \b --clpath command line
//! argument
//!
//! \subsection dep Run-time dependencies
//!
//! \li \b Windows \b Visual \b Studio \b 2008 version: on Windows you will need the Visual Studio 2008 (x86) run-time 
//! library redistributables which you can find at this location: 
//! http://www.microsoft.com/downloads/details.aspx?FamilyID=9b2da534-3e03-4391-8a4d-074b9f2bc1bf&displaylang=en
//! 
//! \li \b Windows \b Visual \b Studio \b 2010 version: on Windows you will need the Visual Studio 2010 (x86) run-time 
//! library redistributables which you can find at this location: 
//! http://www.microsoft.com/download/en/details.aspx?id=5555
//!
//! \section Changelog
//!
//! v0.3 (2012-01-15)
//!
//! \li (CLCC) added --add_headers option to define the binary output format
//! \li (CLCC) added --platform_index/-p and --device_index/-d option for selecting platform & device by index
//! \li (CLCC) added --device_filter option to allow building for specific devices only
//!
//! v0.2 (2011-11-07)
//!
//! \li (CLCC) added --output_path option to allow specification of output filename
//! \li (CLCC) added --platform_filter option to allow building for specific platforms only
//! \li (CLCC) multiple .cl files on the command-line are now compiled as a single program (breaking change)
//! \li (CLCC) added support for passing options to the OpenCL Compiler
//! \li (CLCC) added option to save binaries
//! \li (CLCC) fixed error when calling clCreateContextFromType with NULL argument
//! \li (CLEW) added error code for failing to import a function
//! \li (CLEW) added checking to function importer
//! \li (CLEW) added support for special error codes
//! 
//! v0.1 (2009-12-08)
//! \li Initial setup of code tree, tested under Windows and Mac OS X using
//! Visual Studio 2008 and XCode 3.1
//!
//! \section Todo
//!
//!	\li add support for vender-specific extensions to CLEW
//! \li add support for OpenCL 1.2 specification to CLEW and CLCC
//!
//! \section Credits
//! 
//! CLCC was written by George van Venrooij of Organic Vectory B.V.\n
//! Contact him by e-mailing to: at \b george \e at \b organicvectory \e dot \b com
//!
//! Contributions were made by the following authors:
//!
//! \li Fredrik Orderud
//! \li Ian Cullinan
//! 
//! (c) 2009-2012 Organic Vectory B.V.  -  http://www.organicvectory.com
//!
//! \file main.cpp
//! \brief Main application file

#include "options.hpp"

#include "clew.h"
#include "clpp.hpp"
#include "clinfo.hpp"
#include "output.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/spirit/include/classic.hpp>

#include <fstream>
#include <iostream>

using namespace std;

namespace
{
    struct write_number_a
    {
        write_number_a(string& s, const string& input_file, const int& line_number) 
            :   s_(s)
            ,   input_file_(input_file)
            ,   line_number_(line_number) 
        {}

        //template <typename IterT>
        void operator()(const char*, const char*) const
        {
            boost::format f("%1%(%2%): ");
            f % input_file_;
            f % line_number_;
            s_ += str(f);
        }

    private:
                string&     s_;
        const   string&     input_file_;
        const   int&        line_number_;
    };

    struct append_a
    {
        append_a(string& s) : s_(s) {}

        //template <typename IterT>
        void operator()(const char* first, const char* last) const
        {
            s_.append(first, last);
        }

    private:
        string&    s_;
    };

}

void
create_platform_contexts
    (   const   cl::driver&                     cldriver
    ,   const   options&                        options
    ,           vector<cl::platform>&           build_platforms
    ,           vector<cl::shared_context>&     build_contexts
    ,           vector<vector<cl_device_id> >&  build_device_ids
    )
{
    //  Get options
    const std::string&  platform_name_filter(options.platform_name_filter());
    const std::string&  device_name_filter  (options.device_name_filter());
    cl_device_type      device_type         (options.device_type());
    int                 platform_index      (options.platform_index());
    int                 device_index        (options.device_index());

    if (platform_index >= (int)cldriver.num_platforms())
    {
        BOOST_THROW_EXCEPTION(cl::exception("platform_index setting out of range"));
    }

    //  Create a context for the desired device type for each platform (after applying the platform filter)
    for (cl_uint p = 0; p < cldriver.num_platforms(); p++) 
    {
        //  If platform index is set, only process platform with corresponding index
        if  (   (platform_index != CLCC_ALL_PLATFORMS)
            &&  (platform_index != p)
            )
        {
            continue;
        }

        //  Error value
        cl_int error = CL_SUCCESS;

        //  Get platform
        cl::platform pf(cldriver.get_platform(p));

        //  Check for a filter, if so, check if the platform name matches it
        if (!platform_name_filter.empty())
        {
            //! \note   Workaround: on VS2008 with Boost 1.46.1 we get an error when testing result.empty() in Debug due to iterator checking
            //!         So that's why the strings are first put into plain old const char*'s
            const char* platform_name = pf.name().c_str();
            const char* filter_name   = platform_name_filter.c_str();

            boost::iterator_range<const char*> result = boost::ifind_first(platform_name, filter_name);

            if (result.empty())
            {
                continue;
            }
        }

        cl_context_properties props[] = 
        {   CL_CONTEXT_PLATFORM
        ,   (cl_context_properties)(pf.platform_id())
        ,   0
        };

        //  Create a context on this platform
        cl::shared_context context(clCreateContextFromType(props, device_type, NULL, NULL, &error));

        //  Check for errors
        if (error == CL_DEVICE_NOT_FOUND)
        {
            //  If a platform does not have the device type specified, then report it and continue
            clog << "Platform '" << pf.name() << "' does not contain a device of type " << CLDEVICE_TYPE_ENUM2STRING(device_type) << "\n";

            continue;
        }

        CLCALL(error);

        //  Determine the number of devices in the context
        size_t num_devices = 0;

        //  Get the # of bytes required to store the devices
        CLCALL(clGetContextInfo(context.get(), CL_CONTEXT_DEVICES, 0, NULL, &num_devices));

        //  Translate to # of devices
        num_devices /= sizeof(cl_device_id);

        //  Allocate storage for devices
        vector<cl_device_id> device_ids(num_devices);

        //  Retrieve their ids
        CLCALL(clGetContextInfo(context.get(), CL_CONTEXT_DEVICES, num_devices * sizeof(cl_device_id), &device_ids[0], NULL));


        //  Process device_index settings
        if  (device_index != CLCC_ALL_DEVICES)
        {
            if (device_index >= (int)device_ids.size())
            {
                BOOST_THROW_EXCEPTION(cl::exception("device_index setting out of range"));
            }

            //  Select only indexed device
            device_ids.assign(1, device_ids[device_index]);
        }

        //  Check for a filter, if so, check if the device name matches it
        if (!device_name_filter.empty())
        {
            vector<cl_device_id>    to_erase;

            for (unsigned int d = 0; d < device_ids.size(); ++d)
            {
                cl::device dev(device_ids[d]);

                //! \note   Workaround: on VS2008 with Boost 1.46.1 we get an error when testing result.empty() in Debug due to iterator checking
                //!         So that's why the strings are first put into plain old const char*'s
                const char* device_name = dev.name().c_str();
                const char* filter_name = device_name_filter.c_str();

                boost::iterator_range<const char*> result = boost::ifind_first(device_name, filter_name);

                //  If the match was empty, tag this device id for removal
                if (result.empty())
                {
                    to_erase.push_back(device_ids[d]);
                }
            }

            //  Erase all device id's that didn't match the filter
            //  Use set_difference for that, but before we can, we need to sort the ranges
            sort(device_ids.begin(), device_ids.end());
            sort(to_erase  .begin(), to_erase  .end());
            vector<cl_device_id>            remaining_devices(device_ids.size());
            vector<cl_device_id>::iterator  remaining_devices_end;

            remaining_devices_end = set_difference(device_ids.begin(), device_ids.end(), to_erase.begin(), to_erase.end(), remaining_devices.begin());

            //  Check
            if (remaining_devices_end == remaining_devices.begin())
            {
                //  If a no devices remain for this platform, the skip it
                clog << "Platform '" << pf.name() << "' does not contain a device of type " << CLDEVICE_TYPE_ENUM2STRING(device_type) << " with a name that matches filter " << device_name_filter << "\n";

                continue;
            }

            device_ids.assign(remaining_devices.begin(), remaining_devices_end);
        }

        //  When no errors occurred, add the platform, context and device id'sto the lists
        build_platforms .push_back(pf);
        build_contexts  .push_back(context);
        build_device_ids.push_back(device_ids);
    }
}
void
handle_build_failure
    (   const   vector<cl_device_id>&   device_ids
    ,           cl::shared_program      prg
    ,   const   vector<string>&         input_files
    )
{
    cl_build_status status;

    //  Allocate storage for build log per device
    vector<string>  device_build_logs(device_ids.size());

    //  Per device
    for (size_t d = 0; d < device_ids.size(); ++d)
    {
        //  Retrieve build status
        CLCALL(clGetProgramBuildInfo(prg.get(), device_ids[d], CL_PROGRAM_BUILD_STATUS, sizeof(cl_build_status), &status, NULL));

        //  On error, get the log
        if (status == CL_BUILD_ERROR)
        {
            size_t log_size = 0;
            //  Get size of log
            CLCALL(clGetProgramBuildInfo(prg.get(), device_ids[d], CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size));

            //  Allocate log
            device_build_logs[d].resize(log_size, 0);

            //  Get log
            CLCALL(clGetProgramBuildInfo(prg.get(), device_ids[d], CL_PROGRAM_BUILD_LOG, log_size, &device_build_logs[d][0], NULL));

            //  Insert file path into log
            using namespace boost::spirit::classic;

            string processed_log;

            int line_number = 0;

            rule<>  msg_r   =   *(anychar_p - eol_p) >> eol_p;

            //! \todo   Convert line-number substitution code to a run-time switch. But in order to do that, I will need some
            //!         more outputs from various drivers to determine what the variants are and what the switch variable must be.
#ifdef _MSC_VER
            rule<>  nr_r    =   ch_p(':') >> uint_p[assign_a(line_number)] >> ':';
#endif
#ifdef __GNUC__
            rule<>  nr_r    =   str_p("<program source>:") >> uint_p[assign_a(line_number)] >> ':' >> uint_p >> ':';
#endif
            rule<>  line_r  =   nr_r[write_number_a(processed_log, input_files[0], line_number)] >> msg_r[append_a(processed_log)]
                            |   msg_r[append_a(processed_log)]
                            ;
            rule<>  file_r  =   *line_r;
           
            parse_info<> info = parse
                (   device_build_logs[d].c_str()
                ,   file_r
                );

            if (info.full)
            {
                cerr << processed_log << endl;
            }
            else
            {
                //  Print log
                cerr << input_files[0] << " build error:" << endl << device_build_logs[d] << endl;
            }

            BOOST_THROW_EXCEPTION(cl::exception("build error"));
        }
    }
}

void 
save_to_file 
    (   const   std::string&                    filename
    ,   const   vector<cl::platform>&           build_platforms
    ,   const   vector<vector<cl_device_id> >&  build_device_ids
    ,   const   vector<cl::shared_program>&     build_programs
    ,   const   bool                            add_headers
    )
{
    // check if CLCC headers must be added
    if (!add_headers) 
    {
        // count the number of binaries
        size_t bin_count = 0;
        for (size_t p = 0; p < build_device_ids.size(); p++)
        {
            bin_count += build_device_ids[p].size();
        }
        
        if (bin_count > 1)
            throw std::runtime_error("Must add CLCC headers when output consists of multiple binaries.");
    }

    //  Save binaries to file
    //  For format specification, see help description
    //  Open file
    ofstream file(filename.c_str(), ios::binary);

    //  Check
    if (!file.is_open())
    {
        BOOST_THROW_EXCEPTION(cl::exception(string("could not open output file '") + filename + "'"));
    }

    //  Write general header
    if (add_headers) 
    {
        clcc_binary_header header;
        header.tag              =   'clcc';
        header.version_major    =   CLCC_VERSION_MAJOR;
        header.version_minor    =   CLCC_VERSION_MINOR;
        header.version_revision =   CLCC_VERSION_PATCH;
        header.version_build    =   CLCC_VERSION_BUILD;
        header.platform_count   =   build_platforms.size();

        file.write((const char*)&header, sizeof(clcc_binary_header));
    }

    //  For each platform...
    for (unsigned int p = 0; p < build_platforms.size(); ++p)
    {
        //  Write platform header
        if (add_headers) 
        {
            clcc_binary_platform_header platform_header;

            platform_header.num_devices     = build_device_ids[p].size();

            platform_header.name_length     = build_platforms[p].name   ().size() + 1;
            platform_header.vendor_length   = build_platforms[p].vendor ().size() + 1;
            platform_header.version_length  = build_platforms[p].version().size() + 1;

            file.write((const char*)&platform_header, sizeof(clcc_binary_platform_header));

            //  Write name, vendor and version strings
            file.write(build_platforms[p].name   ().c_str(), platform_header.name_length    );
            file.write(build_platforms[p].vendor ().c_str(), platform_header.vendor_length  );
            file.write(build_platforms[p].version().c_str(), platform_header.version_length );
        }

        //  Allocate space for binary sizes
        vector<size_t> binary_sizes(build_device_ids[p].size());

        //  Retrieve binary sizes
        CLCALL(clGetProgramInfo(build_programs[p].get(), CL_PROGRAM_BINARY_SIZES, sizeof(size_t) * binary_sizes.size(), &binary_sizes[0], NULL));

        //  Allocate binary tables
        vector<char*> binaries(binary_sizes.size());

        for (size_t b = 0; b < binary_sizes.size(); b++)
        {
            binaries[b] = new char[binary_sizes[b]];
        }

        //  Retrieve all binaries
        CLCALL(clGetProgramInfo(build_programs[p].get(), CL_PROGRAM_BINARIES, binary_sizes.size()*sizeof(size_t), &binaries[0], NULL));


        //  For each device, write info & binary
        for (size_t b = 0; b < binary_sizes.size(); ++b) 
        {
            //  Write device header
            if (add_headers) 
            {
                //  Get device
                cl::device dev(build_device_ids[p][b]);

                clcc_binary_device_header device_header;

                device_header.type                  = (unsigned long)dev.device_type();
                device_header.binary_length         = binary_sizes[b];

                device_header.name_length           = dev.name          ().size() + 1;
                device_header.vendor_length         = dev.vendor        ().size() + 1;
                device_header.driver_version_length = dev.driver_version().size() + 1;
                device_header.device_version_length = dev.device_version().size() + 1;
                    
                file.write((const char*)&device_header, sizeof(clcc_binary_device_header));

                //  Write name, vendor, driver version and device version strings
                file.write(dev.name          ().c_str(), device_header.name_length          );
                file.write(dev.vendor        ().c_str(), device_header.vendor_length        );
                file.write(dev.driver_version().c_str(), device_header.driver_version_length);
                file.write(dev.device_version().c_str(), device_header.device_version_length);
            }

            //  Write binary
            file.write(&binaries[b][0], binary_sizes[b]);
        }

        // Free binary tables
        for (size_t b = 0; b < binary_sizes.size(); b++)
        {
            delete [] binaries[b];
        }
    }
}


//! \brief  Main entry point
int main(int argc, char* argv[])
{
    int result = 0;

    try
    {
        //  Check for no arguments
        if (argc == 1)
        {  
            cout << "clcc: no sources\n";
            return 0;
        }

        //  Handle command-line options
        options options(argc, argv);

        //  Dynamically load OpenCL dynamic library
        cl_int error = clewInit(options.clpath().c_str());

        if (error != CLEW_SUCCESS)
        {
            BOOST_THROW_EXCEPTION(cl::exception("could not load opencl.dll"));
        }

        //  Create driver (required)
        cl::driver cldriver;

        //  Print options if requested
        if (options.info() == true)
        {
            //  print info
            cout << cldriver << endl;
        }

        //  Check if we need to do a build
        if (options.build() == true)
        {
            if (cldriver.num_platforms() == 0)
            {
                BOOST_THROW_EXCEPTION(cl::exception("no platforms available"));
            }

            //  For each platform that matches the filter:
            //  - create a context
            //  - retrieve device id's for matching devices
            vector<cl::platform>            build_platforms;
            vector<cl::shared_context>      build_contexts;
            vector<vector<cl_device_id> >   build_device_ids;

            create_platform_contexts
                (   cldriver
                ,   options
                ,   build_platforms
                ,   build_contexts
                ,   build_device_ids
                );

            if (build_platforms.empty())
            {
                BOOST_THROW_EXCEPTION(cl::exception("no build platforms/devices found\n"));
            }

            //  Load all source files into memory
            //  Get list of files
            const vector<string>& input_files = options.input_files();

            //  Vector of strings containing contents of files
            vector<string>  input_files_content(input_files.size());

            //  Vector of strings containing const char* to contents of files
            vector<const char*> sources(input_files.size(), NULL);

            for (size_t f = 0; f < input_files.size(); ++f)
            {
                //  Open file
                ifstream file(input_files[f].c_str());

                //  Check for errors
                if (!file)
                {
                    BOOST_THROW_EXCEPTION(cl::exception(string("could not open file '") + input_files[f] + "'"));
                }

                //  Read contents
                istreambuf_iterator<char> begin(file.rdbuf());
                istreambuf_iterator<char> end;

                //  Store in string object
                input_files_content[f].assign(begin, end);

                //  Store source addresses
                sources[f] = input_files_content[f].c_str();
            }



            //  Create a program for all contexts
            vector<cl::shared_program>      build_programs  (build_contexts.size());

            for (size_t p = 0; p < build_contexts.size(); ++p)
            {
                //  Compile all files as a single program
                build_programs[p] = clCreateProgramWithSource(build_contexts[p].get(), sources.size(), &sources[0], NULL, &error);
                CLCALL(error);

                //  Build program, pass options to OpenCL Compiler
                error = clBuildProgram(build_programs[p].get(), 0, NULL, options.cloptions().c_str(), NULL, NULL);

                //  Check for build errors
                if (error != CL_SUCCESS)
                {
                    handle_build_failure(build_device_ids[p], build_programs[p], input_files);
                }
            }

            save_to_file(options.output_file(), build_platforms, build_device_ids, build_programs, options.add_headers());
        }
    }
    catch (const cl::exception&)
    {
        //  Silence exception

        //  But return an error
        result = -1;
    }
    catch (const boost::exception& e)
    {
        //! \todo   Handle possible errors which might arise from compilation or other errors more gracefully
        //!         i.e. give the user more info about the error and possible solutions

        using namespace boost;

        //  Extract filename
        if (char const * const * f = get_error_info<throw_file>(e))
        {
            cerr << *f;

            //  Extract line number
            if (int const * l = get_error_info<throw_line>(e))
            {
                cerr << '(' << *l << "):";
            }
            else
            {
                cerr << "(<unknown>):";
            }

            cerr << " boost::exception thrown ";

            if (char const * const * fn = get_error_info<throw_function>(e))
            {
                cerr << " in function " << *fn << '\n';
            }

            if (const std::exception* se = dynamic_cast<const std::exception*>(&e))
            {
                cerr << se->what() << '\n';
            }
        }
        
        result = -1;
    }
    catch (const exception& e)
    {
        cerr << "std::exception caught\n\t" << e.what() << endl;

        result = -1;
    }
    catch (...)
    {
        cerr << "Unknown exception caught." << endl;

        result = -1;
    }

    return result;
}
