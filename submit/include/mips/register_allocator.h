#ifndef REGISTER_ALLOCATOR_H
#define REGISTER_ALLOCATOR_H
#include "mips_reg.h"
#include "mips_utils.h"
#include <vector>
#include <unordered_map>
#include <set>

class RegisterAllocator {
    // virtual <=> physical
    std::unordered_map<int, int> vreg_preg_map;
    // physical <=> virtual
    std::unordered_map<int, int> preg_vreg_map;
    // physical
    std::set<int> temp_regs_pool;

    public:
    RegisterAllocator() {
        // t0 - t7 s0 - s7
        for (int i = 8; i < 16; i++) {
            temp_regs_pool.insert(i);
        }
        for (int i = 16; i < 24; i++) {
            temp_regs_pool.insert(i);
        }
    }

    MipsReg* allocate_register(int vreg_id) {
        if (vreg_preg_map.find(vreg_id) != vreg_preg_map.end()) {
            std::cout << "virtual register " << vreg_id << " has already been allocated!" << std::endl;
            int preg_id = vreg_preg_map[vreg_id];
            return parse_id_to_reg(preg_id);
        } else if (!temp_regs_pool.empty()) {
            auto it = temp_regs_pool.begin();
            temp_regs_pool.erase(it);
            vreg_preg_map[vreg_id] = *it;
            preg_vreg_map[*it] = vreg_id;
            MipsReg* preg = parse_id_to_reg(*it);
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
        int preg_id = vreg_preg_map[vreg_id];
        vreg_preg_map.erase(vreg_id);
        preg_vreg_map.erase(preg_id);
        temp_regs_pool.insert(preg_id);
    }

    MipsReg* virtual_2_physical(int vreg_id) {
        if (vreg_preg_map.find(vreg_id) == vreg_preg_map.end()) {
            std::cout << "virtual register %d has not been allocated!" << vreg_id << std::endl;
            return nullptr;
        }
        int preg_id = vreg_preg_map[vreg_id];
        free_register(vreg_id);
        return parse_id_to_reg(preg_id);
    }

    int physical_2_virtual(MipsReg* preg) {
        int preg_id = parse_reg_to_id(preg);
        if (preg_vreg_map.find(preg_id) == preg_vreg_map.end()) {
            std::cout << "physical register has not been allocated!" << std::endl;
            return -1;
        }
        return preg_vreg_map[preg_id];
    }

    void move_register(int src_vreg_id, int dst_vreg_id) {
        if (vreg_preg_map.find(src_vreg_id) == vreg_preg_map.end()) {
            std::cout << "virtual register %d has not been allocated!" << src_vreg_id << std::endl;
            return;
        }
        int preg_id = vreg_preg_map[src_vreg_id];
        vreg_preg_map.erase(src_vreg_id);
        preg_vreg_map.erase(preg_id);
        vreg_preg_map[dst_vreg_id] = preg_id;
        preg_vreg_map[preg_id] = dst_vreg_id;
    }

    std::vector<MipsReg*> get_active_registers() {
        std::vector<MipsReg*> active_regs;
        for (auto it = vreg_preg_map.begin(); it != vreg_preg_map.end(); it++) {
            active_regs.push_back(parse_id_to_reg(it->second));
        }
        return active_regs;
    }

    bool is_active_register(MipsReg* preg) {
        int preg_id = parse_reg_to_id(preg);
        return preg_vreg_map.find(preg_id) != preg_vreg_map.end();
    }
    
};

#endif // REGISTER_ALLOCATOR_H