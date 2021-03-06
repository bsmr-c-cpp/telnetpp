#pragma once

#include "telnetpp/detail/router.hpp"
#include "telnetpp/command.hpp"
#include "telnetpp/element.hpp"

namespace telnetpp { namespace detail {

struct command_router_key_from_message_policy
{
    static command key_from_message(command const &cmd)
    {
        return cmd;
    }
};

class command_router
  : public router<
        command,
        command,
        std::vector<token>,
        detail::command_router_key_from_message_policy
    >
{
};

}}
