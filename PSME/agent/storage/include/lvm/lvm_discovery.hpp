/*!
 * @copyright
 * Copyright (c) 2015-2016 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *
 * @file lvm_discovery.hpp
 * @brief Lvm discovery interface
 * */

#ifndef PSME_AGENT_STORAGE_LVM_LVM_DISCOVERY_HPP
#define PSME_AGENT_STORAGE_LVM_LVM_DISCOVERY_HPP

#include <vector>

struct lvm;
struct volume_group;
struct logical_volume;
struct physical_volume;

namespace agent {
namespace storage {
namespace lvm {

class VolumeGroup;
class LogicalVolume;
class PhysicalVolume;

/*! @brief Class for discovering lvm in the system */
class LvmDiscovery {
public:
    using VolumeGroupVec = std::vector<VolumeGroup>;

    /*!
     * @brief Constructor
     * @param lvm Pointer to main lvm structure
     * */
    explicit LvmDiscovery(struct lvm* lvm);

    /*!
     * @brief Do discovery in the system
     * @return Collection of VolumeGroup
     * */
    VolumeGroupVec discovery();
private:
    void discovery_physical_volumes(volume_group* handle, VolumeGroup& group);
    void discovery_logical_volumes(volume_group* handle, VolumeGroup& group);

    VolumeGroup
    make_volume_group(volume_group* handle, const char* name) const;

    LogicalVolume
    make_logical_volume(volume_group* group, logical_volume* handle) const;

    PhysicalVolume
    make_physical_volume(volume_group* group, physical_volume* handle) const;

    struct lvm* m_lvm{nullptr};
};

}
}
}
#endif	/* PSME_AGENT_STORAGE_LVM_LVM_DISCOVERY_HPP */
