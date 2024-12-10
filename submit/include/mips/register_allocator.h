#ifndef REGISTER_ALLOCATOR_H
#define REGISTER_ALLOCATOR_H
#include "mips_reg.h"
#include <vector>
#include <unordered_map>
#include <set>

struct MipsRegComparator {
    bool operator()(const MipsReg* lhs, const MipsReg* rhs) const {
        if (lhs->type == TempRegType && rhs->type == SavedRegType) return true;
        if (lhs->type == SavedRegType && rhs->type == TempRegType) return false;
        return lhs->index < rhs->index;
    }
};

class RegisterAllocator {
    std::unordered_map<int, MipsReg*> vreg_preg_map;
    std::unordered_map<MipsReg*, int> preg_vreg_map;
    std::set<MipsReg*, MipsRegComparator> temp_regs_pool;

    public:
    RegisterAllocator() {
        for (int i = 0; i < 8; i++) {
            temp_regs_pool.insert(new TempReg(i));
        }
        for (int i = 0; i < 8; i++) {
            temp_regs_pool.insert(new SavedReg(i));
        }
    }

    MipsReg* allocate_register(int vreg_id) {
        if (vreg_preg_map.find(vreg_id) != vreg_preg_map.end()) {
            std::cout << "virtual register " << vreg_id << " has already been allocated!" << std::endl;
            return vreg_preg_map[vreg_id];
        } else if (!temp_regs_pool.empty()) {
            auto it = temp_regs_pool.begin();
            MipsReg* preg = *it;
            temp_regs_pool.erase(it);
            vreg_preg_map[vreg_id] = preg;
            preg_vreg_map[preg] = vreg_id;
            return preg;
        }
        std::cout << "No available physical register!" << std::endl;
        return nullptr;
    }

    void free_register(int vreg_id) {
        if (vreg_preg_map.find(vreg_id) == vreg_preg_map.end()) {
            std::cout << "virtual register " << vreg_id << " has not been allocated!" << std::endl;
            return;
        }
        MipsReg* preg = vreg_preg_map[vreg_id];
        vreg_preg_map.erase(vreg_id);
        preg_vreg_map.erase(preg);
        temp_regs_pool.insert(preg);
    }

    MipsReg* virtual_2_physical(int vreg_id) {
        if (vreg_preg_map.find(vreg_id) == vreg_preg_map.end()) {
            std::cout << "virtual register %d has not been allocated!" << vreg_id << std::endl;
            return nullptr;
        }
        return vreg_preg_map[vreg_id];
    }

    int physical_2_virtual(MipsReg* preg) {
        if (preg_vreg_map.find(preg) == preg_vreg_map.end()) {
            std::cout << "physical register has not been allocated!" << std::endl;
            return -1;
        }
        return preg_vreg_map[preg];
    }

    void move_register(int src_vreg_id, int dst_vreg_id) {
        if (vreg_preg_map.find(src_vreg_id) == vreg_preg_map.end()) {
            std::cout << "virtual register %d has not been allocated!" << src_vreg_id << std::endl;
            return;
        }
        MipsReg* preg = vreg_preg_map[src_vreg_id];
        vreg_preg_map.erase(src_vreg_id);
        preg_vreg_map.erase(preg);
        vreg_preg_map[dst_vreg_id] = preg;
        preg_vreg_map[preg] = dst_vreg_id;
    }

    std::vector<MipsReg*> get_active_registers() {
        std::vector<MipsReg*> active_regs;
        for (auto it = vreg_preg_map.begin(); it != vreg_preg_map.end(); it++) {
            active_regs.push_back(it->second);
        }
        return active_regs;
    }

    bool is_active_register(MipsReg* preg) {
        return preg_vreg_map.find(preg) != preg_vreg_map.end();
    }
    
};

#endif // REGISTER_ALLOCATOR_H