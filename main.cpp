#include <boost/program_options.hpp>

#include <iostream>
#include <typeinfo>
#include <stdexcept>
#include <string>

#include "diashow.h"

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
            throw std::runtime_error("seconds <= 0");
        }
    }

    if(vm.count("d"))
    {
        directory = vm["d"].as<std::string>();
    }
    else
    {
        throw std::runtime_error("-d is required");
    }

    Diashow dia(directory, seconds);

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
    std::cerr << "i3diashow: error catched in main( " << typeid(ex).name() << " )\n";
    std::cerr << "what: " << ex.what() << "\n";
}
catch(...)
{
    std::cerr << "i3diashow: error catched in main( unknown exception type )\n";
}


