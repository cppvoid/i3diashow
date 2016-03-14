#include <boost/program_options.hpp>

#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <string>

#include "diashow.h"

extern "C"
{
	#include "daemon.h"
	#include <syslog.h>
}

#include <string>

int main(int argc, char** argv) try
{
	boost::program_options::options_description description("i3diashow -s { update picture in seconds } -d { directory } -r { random }");

    description.add_options()
    ( "s", boost::program_options::value<int>() ,"update picture in seconds" )
    ( "d", boost::program_options::value<std::string>() ,"directory" )
    ( "r", "random");

    boost::program_options::variables_map vm;
    boost::program_options::store( boost::program_options::command_line_parser( argc, argv )
                                   .options(description )
                                   .style( boost::program_options::command_line_style::unix_style
                                         | boost::program_options::command_line_style::allow_long_disguise ).run(), vm );

    boost::program_options::notify( vm );

    int seconds = 10;
    std::string directory;

    if(vm.count("s"))
    {
        seconds = vm["s"].as<int>();

        if(seconds <= 0)
        {
			std::cerr << "i3diashow: seconds <= 0\n";
        }
    }

    if(vm.count("d"))
    {
        directory = vm["d"].as<std::string>();
    }
    else
    {
		std::cerr << ("i3diashow: -d is required\n");
    }

    Diashow dia(directory, seconds);

	if(!createDaemon())
	{
		syslog(LOG_CRIT, "error while creating daemon");

		return 1;
	}

    if(vm.count("r"))
    {
        dia.runRandom();
    }
    else
    {
        dia.runAfterRow();
    }
}
catch(const std::exception& ex)
{
    syslog(LOG_CRIT, "%s", ex.what());
	closelog();
}
catch(...)
{
	syslog(LOG_CRIT, "unknown error");
	closelog();
}


