#include "ExecutionDescription.hh"
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
namespace pt = boost::posix_time;
#include <boost/asio.hpp>
namespace ip = boost::asio::ip;

namespace
{
    std::string get_date()
    {
        const pt::ptime now = pt::second_clock::local_time();
        return to_iso_extended_string(now);
    }

    std::string get_user()
    {
        const std::string user(getlogin());
        return user;
    }

    std::string get_hostname()
    {
        const std::string& hostname = ip::host_name();

        return hostname;
    }

    std::string get_wd()
    {
        const std::string wd = 
            boost::filesystem::current_path().string();

        return wd;
    }

    std::string get_cmd(const Settings& settings)
    {
        std::ostringstream oss;

        oss << settings.executable_name << 
            " --count-matrix  " << settings.input.count_matrix_file <<
            " --target-read-count " << settings.downsizing.target_read_count <<
            " --num-repetitions " << settings.downsizing.num_repetitions <<
            " --seed " << settings.downsizing.seed <<
            " --num-threads " << settings.downsizing.num_threads; 

        if (settings.output.downsized_count_matrix_file != "")
        {
            oss << " --downsized-matrix " << settings.output.downsized_count_matrix_file;
        }
        if (settings.output.stats_file != "")
        {
            oss << " --stats " << settings.output.stats_file;
        }

        return oss.str();
    }
};

ExecutionDescription::ExecutionDescription(const Settings& settings)
    : date(get_date()),
    user(get_user()),
    hostname(get_hostname()),
    wd(get_wd()),
    cmd(get_cmd(settings)),
    program_version(__APP_VERSION__)
{}

