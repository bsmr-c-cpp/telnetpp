#pragma once

#include "telnetpp/detail/return_default.hpp"
#include <functional>
#include <map>
#include <type_traits>
#include <utility>

namespace telnetpp { namespace detail {

//* =========================================================================
/// \class router
/// \brief A class template to route messages.
/// \param Key A token that identifies the handler for a message.  It must
/// be derivable from a message in some way.
/// \param Message A message that this router receives and must forward
/// appropriately.
/// \param KeyFromMessagePolicy A template class that implements the
/// following function: \code
/// static void KeyFromMessagePolicy::key_from_message(Message const &message)
/// \endcode This function should return a Key that is derived from the
/// Message.
///
/// A class template that receives messages and forwards them on to
/// appropriate handlers.
///
/// \par Usage
/// Create an instance of the class, passing the necessary template parameters.
/// For this demonstration, we will use a char as a Key, a string as a Message,
/// and a hypothetical class first_element<> that returns the first
/// element of the string as its key.
/// \par
/// \code router<char, std::string, void, first_element> route; \endcode
/// \par
/// We want to forward any strings beginning with the letter 'z' to a
/// hypothetical function, "z_handler".
/// \par
/// \code route.register_route('z', z_handler); \endcode
/// \par
/// Anything else should go to a hypothetical function "unwanted_handler".
/// \par
/// \code route.set_unregistered_route(unwanted_handler); \endcode
/// \par
/// Given a vector<std::string> called "vec", we want to route all of the
/// strings therein.
/// \par
/// \code std::for_each(vec.begin(), vec.end(), route); \endcode
//* =========================================================================
template <
    class Key,
    class Message,
    class Result,
    class KeyFromMessagePolicy
>
class router
{
public :
    typedef Key                                    key_type;
    typedef Message                                message_type;
    typedef Result                                 result_type;
    typedef std::function<Result (Message const&)> function_type;
    typedef std::map
    <
        key_type,
        function_type
    > registered_functions_map_type;

    //* =====================================================================
    /// \brief Register a route for messages with a particular key.
    ///
    /// Register a route that will later on be taken by any message received
    /// that contains the specified key.
    //* =====================================================================
    template <typename KeyType, typename Function>
    void register_route(
        KeyType  &&key,
        Function &&function)
    {
        registered_functions_[std::forward<KeyType>(key)] =
            std::forward<Function>(function);
    }

    //* =====================================================================
    /// \brief Unregisters a route for messages with a particular key.
    ///
    /// Unregister a route that will no longer be taken by any message
    /// received that contains the specified key.
    //* =====================================================================
    template <typename KeyType>
    void unregister_route(KeyType &&key)
    {
        registered_functions_.erase(std::forward<KeyType>(key));
    }

    //* =====================================================================
    /// \brief Set a route for messages with an unregistered key.
    ///
    /// Register a route that will be taken by any message received that has
    /// a key for which a route has not been registered.
    //* =====================================================================
    template <typename Function>
    void set_unregistered_route(Function &&route)
    {
        unregistered_route_ = std::forward<Function>(route);
    }

    //* =====================================================================
    /// \brief Route a message.
    ///
    /// Routes a message.  If the key for the message has a registered route,
    /// then it will be forwarded to that handler.  Otherwise, if there is
    /// an unregistered route, then the message will be forwarded to that
    /// handler instead.
    //* =====================================================================
    Result operator()(Message const& message) const
    {
        auto iter = registered_functions_.find(
            KeyFromMessagePolicy::key_from_message(message));

        if (iter != registered_functions_.end())
        {
            return iter->second(message);
        }
        else if (unregistered_route_ != nullptr)
        {
            return unregistered_route_(message);
        }

        // This garbage is just to return either a default-constructed Result,
        // or void if Result is void.
        return detail::return_default_constructed<Result>{}();
    }

private :
    registered_functions_map_type registered_functions_;
    function_type                 unregistered_route_;
};

}}
