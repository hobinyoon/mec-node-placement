#include <iostream>

#include <boost/regex.hpp>

#include "cons.h"
#include "conf.h"
#include "util.h"


using namespace std;

namespace Conf {
	namespace po = boost::program_options;
	po::variables_map _vm;

	void _ParseArgs(int argc, char* argv[]) {
		po::options_description od("Allowed options");
		od.add_options()
			("in_file", po::value<string>()->default_value("~/work/castnet-data/youtube/150505-104600-tweets-6mo"), "Input file name")
			("out_file", po::value<string>()->default_value(".result/output"), "Output file name")
			("help", "show help message")
			;

		po::positional_options_description pod;
		pod.add("in_file", 1);
		pod.add("out_file", 1);

		po::store(po::command_line_parser(argc, argv).options(od).positional(pod).run(), _vm);
		po::notify(_vm);

		if (_vm.count("help") > 0) {
			// well... this doesn't show boolean as string.
			cout << std::boolalpha;
			cout << od << "\n";
			exit(0);
		}
	}

	void Init(int argc, char* argv[]) {
		_ParseArgs(argc, argv);
	}

	const string GetDir(const string& k) {
		// Use boost::regex. C++11 regex works from 4.9. Ubuntu 14.04 has g++ 4.8.4.
		//   http://stackoverflow.com/questions/8060025/is-this-c11-regex-error-me-or-the-compiler
		return boost::regex_replace(
				_vm[k].as<string>()
				, boost::regex("~")
				, Util::HomeDir());
	}
};
