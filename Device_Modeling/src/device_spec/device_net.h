/**
 * @file device_net.h
 * @brief Contains the declaration of the device_net class.
 * @version 0.1
 * @date 2023-05-18
 * @author Manadher Kharroubi (manadher@rapidsilicon.com)
 */

#pragma once

#include <string>
#include <set>
#include <memory>
#include <ostream>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/core.h>
#include <spdlog/fmt/bundled/format.h>

class device_block;

/**
 * @class device_net
 * @brief Class representing a net in a device.
 *
 * A net is used to conduct bit values within a device/block instance.
 */
class device_net
{
public:
    /**
     * @brief Constructor that initializes the device_net.
     * @param net_name The name of the net.
     * @param signal_name The name of the associated signal.
     */
    device_net(const std::string &net_name, const std::string &signal_name)
        : net_name_(net_name), signal_name_(signal_name)
    {
        spdlog::info("Creating net with name: {}", net_name_);
    }

    /**
     * @brief Copy constructor for device_net.
     * @param other The device_net to copy.
     */
    device_net(const device_net &other)
        : net_name_(other.net_name_), signal_name_(other.signal_name_)
    {
        spdlog::info("Creating net with name: {}", net_name_);
    }

    /**
     * @brief Get the name of the net.
     * @return The name of the net.
     */
    std::string get_net_name() const { return net_name_; }

    /**
     * @brief Set the name of the net.
     * @param net_name The name of the net.
     */
    void set_net_name(const std::string &net_name)
    {
        spdlog::info("Setting net name to {}", net_name);
        net_name_ = net_name;
    }

    /**
     * @brief Get the name of the associated signal.
     * @return The name of the associated signal.
     */
    std::string get_signal_name() const { return signal_name_; }

    /**
     * @brief Set the name of the associated signal.
     * @param signal_name The name of the associated signal.
     */
    void set_signal_name(const std::string &signal_name)
    {
        spdlog::info("Setting signal name to {}", signal_name);
        signal_name_ = signal_name;
    }

    /**
     * @brief Get the source net.
     * @return The source net.
     */
    device_net* get_source() const { return source_; }

    /**
     * @brief Set the source net.
     * @param source The source net.
     */
    void set_source(device_net* source)
    {
        spdlog::info("Setting source to {}", source->get_net_name());
        source_ = source;
    }

    /**
     * @brief Get the set of sink nets.
     * @return The set of sink nets.
     */
    const std::set< device_net* > &get_sink_set() const { return sink_set_; }

    /**
     * @brief Add a sink net to the set of sinks.
     * @param sink The sink net to add.
     */
    void add_sink(device_net* sink)
    {
        spdlog::info("Adding sink {}", sink->get_net_name());
        sink_set_.insert(sink);
    }

    /**
     * @brief Equality comparison operator for device_net objects.
     * @param other The other device_net to compare with.
     * @return True if the device_net objects are equal, false otherwise.
     */
    bool operator==(const device_net &other) const
    {
        return (this == &other);
    }

    /**
     * @brief Check if two device_net objects are equal.
     * @param other The other device_net to compare with.
     * @return True if the device_net objects are equal, false otherwise.
     */
    bool equal(const device_net &other) const
    {
        if (net_name_ != other.net_name_ ||
            signal_name_ != other.signal_name_ ||
            source_ != other.source_ ||
            sink_set_.size() != other.sink_set_.size())
        {
            return false;
        }

        for (const auto &sink : sink_set_)
        {
            if (other.sink_set_.count(sink) == 0)
            {
                return false;
            }
        }

        return true;
    }

    /**
     * @brief Inequality comparison operator for device_net objects.
     * @param other The other device_net to compare with.
     * @return True if the device_net objects are not equal, false otherwise.
     */
    bool operator!=(const device_net &other) const
    {
        return !(*this == other);
    }

    /**
     * @brief Output stream operator for device_net.
     * @param os The output stream.
     * @param dn The device_net to output.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os, const device_net &dn)
    {
        os << "Net Name: " << dn.get_net_name() << "\n"
           << "Signal Name: " << dn.get_signal_name() << "\n"
           << "Source: ";
        if (dn.get_source())
        {
            os << dn.get_source()->get_net_name();
        } else {
            os << "null";
        }
        os << "\n"
           << "Sinks: ";
        for (const auto &sink : dn.get_sink_set())
        {
            os << sink->get_net_name() << " ";
        }
        return os;
    }

    /**
     * @brief Convert the device_net to a string representation.
     * @return A string representation of the device_net.
     */
    std::string to_string() const
    {
        std::ostringstream os;
        os << "Net Name: " << get_net_name() << "\n"
           << "Signal Name: " << get_signal_name() << "\n"
           << "Source: ";
        if (get_source())
        {
            os << get_source()->get_net_name();
        }
        os << "\n"
           << "Sinks: ";
        for (const auto &sink : get_sink_set())
        {
            os << sink->get_net_name() << " ";
        }
        return os.str();
    }

    /**
     * @brief Get the formatted string representation of the device_net.
     * @return The formatted string representation.
     */
    std::string to_formatted_string() const
    {
        return fmt::format("device_net: {}", to_string());
    }
private:
    std::string net_name_;
    std::string signal_name_;
    device_net* source_;
    std::set<device_net*> sink_set_;
};

namespace fmt {
    template <>
    struct formatter<device_net*> {
        template <typename ParseContext>
        constexpr auto parse(ParseContext& ctx) {
            return ctx.begin();
        }

        template <typename FormatContext>
        auto format(const device_net* p, FormatContext& ctx) {
            if (p) {
                return format_to(ctx.out(), "device_net: {}", p->to_string());  // Format the underlying device_net object
            } else {
                return format_to(ctx.out(), "device_net: null");
            }
        }
    };
}

