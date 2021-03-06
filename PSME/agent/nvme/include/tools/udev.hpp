/*!
 * @brief Definition of UDev class.
 *
 * @header{License}
 * @copyright Copyright (c) 2015-2018 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @header{Files}
 * @file udev.hpp
 */

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <libudev.h>

namespace agent {
namespace nvme {
namespace tools {

/*! UDev class to get network interfaces list */
class UDev {
public:

    /*!
     * @brief Default constructor.
     */
    UDev() = default;

    /*!
     * @brief Copy constructor.
     */
    UDev(const UDev&) = delete;

    /*!
     * @brief Copy operator.
     */
    UDev& operator=(const UDev&) = delete;

    /*!
     * @brief Default destructor.
     */
    virtual ~UDev() = default;

    /*!
     * @brief Get interface list for given driver optionally filtered by prefix.
     *
     * @param[in] driver driver name.
     * @param[in] match_prefix optional prefix name for filtering.
     *
     * @return Interface list.
     */
    const std::vector<std::string> get_interface_list(const std::string& driver,
                                                      const std::string& match_prefix) const;

private:

    /*!
     * @brief Get port list.
     * @param[in] driver Driver name.
     * @return driver entry list.
     */
    const std::vector<std::string> get_driver_entries(const std::string& driver) const;

    /* Udev deleter */
    struct UdevDeleter {
        void operator()(struct udev* ctx) const {
            udev_unref(ctx);
        }
    };

    /* Udev device deleter */
    struct UdevDeviceDeleter {
        void operator()(struct udev_device* dev) const {
            udev_device_unref(dev);
        }
    };

    /* Udev enumerate deleter */
    struct UdevEnumDeleter {
        void operator()(struct udev_enumerate* udev_enum) const {
            udev_enumerate_unref(udev_enum);
        }
    };
    using Udev = std::unique_ptr<struct udev, UdevDeleter>;
    using UdevDevice = std::unique_ptr<struct udev_device, UdevDeviceDeleter>;
    using UdevEnum = std::unique_ptr<struct udev_enumerate, UdevEnumDeleter>;
};

}
}
}

