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
	#include <sys/types.h>
}

int main(int argc, char** argv) try
{
	boost::program_options::options_description description("Allowed options");
    boost::program_options::variables_map vm;

	try
	{
		description.add_options()
		("help, h", "print usage message")
		("seconds, s", boost::program_options::value<int>(), "update duration")
		("directory, d", boost::program_options::value<std::string>(), "directory")
		("random, r", "random");

		boost::program_options::store(boost::program_options::command_line_parser(argc, argv)
									.options(description)
									.style(
											boost::program_options::command_line_style::unix_style |
											boost::program_options::command_line_style::allow_long_disguise)
									.run(),
									vm);

		boost::program_options::notify(vm);
	}
	catch(const std::exception& ex)
	{
		std::cout << "i3diashow: " << ex.what() << std::endl;

		return -1;
	}

    int seconds = 10;
    std::string directory;

	if(vm.count("help"))
	{
		std::cout << description << "\n";

		return 0;
	}

    if(vm.count("seconds"))
    {
        seconds = vm["seconds"].as<int>();

        if(seconds <= 0)
        {
			std::cerr << "i3diashow: seconds <= 0\n";

			return -1;
		}
    }

    if(vm.count("directory"))
    {
        directory = vm["directory"].as<std::string>();
    }
    else
    {
		std::cerr << "i3diashow: -d is required\n";

		return -1;
	}

    Diashow dia(directory, seconds);

	if((createDaemon()) != 0)
	{
		openlog("i3diashow", LOG_PID, LOG_DAEMON);
		syslog(LOG_CRIT, "error while creating daemon");
		closelog();

		return -1;
	}

	openlog("i3diashow", LOG_PID, LOG_DAEMON);
	syslog(LOG_INFO, "daemon started");

	if(vm.count("random"))
    {
        dia.runRandom();
    }
    else
    {
        dia.runAfterRow();
    }

	closelog();
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


