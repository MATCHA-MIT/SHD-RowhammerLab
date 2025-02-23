#include <algorithm>
#include <array>
#include <tuple>
#include <ranges>
#include <numeric>

#include "../shared.hh"
#include "../params.hh"
#include "../util.hh"

#define BANKS 16
#define THRESHOLD 1000
#define CONSISTENCY_RATE 0.90

/*
 * bin_rows
 *
 * Bins a selection of addresses in the range of [starting_addr, final_addr)
 * based on measure_bank_latency.
 *
 * Input: starting and ending addresses
 * Output: An array of 16 vectors, each of which holds addresses that share the same bank
 *
 */
std::array<std::vector<uint64_t>, BANKS> bin_rows(uint64_t starting_addr, uint64_t final_addr) {
    // TODO - Exercise 3-1
    std::array<std::vector<uint64_t>, BANKS> bins;
    return bins;
}

/*
 *
 * DO NOT MODIFY BELOW ME
 *
 */

std::tuple<uint64_t, double> get_most_frequent(const std::vector<uint64_t>& data) {
    std::map<uint64_t, uint64_t> freq_map;

    for (const auto& item : data) {
        freq_map[item]++;
    }

    auto [most_freq, max_count] = std::accumulate(
        freq_map.begin(),
        freq_map.end(),
        std::pair<uint64_t, uint64_t>{0, 0},
        [](const auto& best, const auto& current) {
            return current.second > best.second ? 
                std::pair{current.first, current.second} : best;
        }
    );

    return {most_freq, static_cast<double>(max_count) / data.size()};
}

inline uint64_t get_bit(uint64_t x, int bit) {
    return (x >> bit) & 1;
}

template <size_t LEN>
std::optional<uint64_t> find_candidate_function(const std::array<std::vector<uint64_t>, LEN>& bins) {
    std::optional<uint64_t> result = std::nullopt;

    std::array<std::function<uint64_t(uint64_t)>, 3> functions = {
        [](uint64_t x) {
            return ((get_bit(x, 16) ^ get_bit(x, 18)) << 3) | 
                   ((get_bit(x, 13) ^ get_bit(x, 19)) << 2) | 
                   ((get_bit(x, 15) ^ get_bit(x, 18)) << 1) |
                   (get_bit(x, 14) ^ get_bit(x, 20));
        },
        [](uint64_t x) {
            return ((get_bit(x, 15) ^ get_bit(x, 19)) << 3) | 
                   ((get_bit(x, 14) ^ get_bit(x, 18)) << 2) | 
                   ((get_bit(x, 13) ^ get_bit(x, 17)) << 1) |
                   (get_bit(x, 16) ^ get_bit(x, 20));
        },
        [](uint64_t x) {
            return ((get_bit(x, 13) ^ get_bit(x, 18)) << 3) | 
                   ((get_bit(x, 14) ^ get_bit(x, 17)) << 2) | 
                   ((get_bit(x, 16) ^ get_bit(x, 19)) << 1) |
                   (get_bit(x, 15) ^ get_bit(x, 20));
        },
    };

    for (size_t i = 0; i < functions.size(); i++) {
        auto &f = functions[i];
        bool good = true;
        for (auto &bin: bins) {
            uint64_t match_count = 0;
            std::vector<uint64_t> bank_comp(bin.size());
            std::transform(bin.begin(), bin.end(), bank_comp.begin(), f);
            auto [id, freq] = get_most_frequent(bank_comp);
            if (freq < CONSISTENCY_RATE) {
                good = false;
                break;
            }
        }
        if (good) {
            // conflicting results
            if (result.has_value())
                return std::nullopt;
            result = i;
        }
    }

    return result;
}

int main (int ac, char **av) {
    
    setvbuf(stdout, NULL, _IONBF, 0);

    // Allocate a large pool of memory (of size BUFFER_SIZE_MB) pointed to
    // by allocated_mem
    allocated_mem = allocate_pages(BUFFER_SIZE_MB * 1024UL * 1024UL);
 
    // Setup PPN_VPN_map
    setup_PPN_VPN_map(allocated_mem, PPN_VPN_map);

    auto result = find_candidate_function(
        bin_rows((uint64_t)allocated_mem, (uint64_t)allocated_mem + ROW_SIZE * 4096));

    if (result.has_value()) {
        printf("Identified function %lu as correct\n", result.value());
    } else {
        puts("Did not identify a correct function :(");
    }
}