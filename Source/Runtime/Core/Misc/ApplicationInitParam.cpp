
#include <boost/program_options.hpp>
#include "ApplicationInitParam.h"

using namespace mikasa::Runtime::Core;
namespace po = boost::program_options;

ApplicationInitParam::ApplicationInitParam(int argc, char **argv)
{
    po::options_description desc("Allowed options");
    desc.add_options()
            ("help,H", "produce help message")
            ("screen-width", po::value<int>(&WindowWidth)->default_value(1024), "screen width")
            ("screen-height", po::value<int>(&WindowHeight)->default_value(768), "screen height")
            ("screen-offset-x", po::value<int>(&WindowOffsetX)->default_value(0), "windows offset x")
            ("screen-offset-y", po::value<int>(&WindowOffsetY)->default_value(0), "windows offset y")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
}
