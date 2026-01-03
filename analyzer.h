#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <array>

struct ZoneCount {
    std::string zone;
    long long count;
};

struct SlotCount {
    std::string zone;
    int hour;              // 0–23
    long long count;
};

class TripAnalyzer {
public:
    // CSV dosyasını işle, hatalı satırları atla, asla çökme
    void ingestFile(const std::string& csvPath);

    // En çok sefer yapılan K bölge: sayıya göre azalan, bölge ismine göre artan
    std::vector<ZoneCount> topZones(int k = 10) const;

    // En yoğun K zaman dilimi: sayıya göre azalan, bölge artan, saat artan
    std::vector<SlotCount> topBusySlots(int k = 10) const;

private:
    // Her bölge için istatistikleri tutan yapı
    struct ZoneStats {
        long long total_trips = 0;
        std::array<long long, 24> hourly_trips = {0}; // 0-23 saatleri için sayaç
    };

    // Bölge adına göre eşlenmiş veriler (Hash Map - O(1) erişim)
    std::unordered_map<std::string, ZoneStats> m_data;
};
