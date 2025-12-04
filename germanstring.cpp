
#include <bits/stdc++.h>
class GermanString16B {
private:
    struct Short {
        uint8_t len;        
        char content[15];   
    };

    struct Long {
        uint32_t len;     
        uint32_t prefix;   
        char* data_ptr;  
    };

    union Representation {
        Short short_rep;
        Long long_rep;
        } rep;
    
    public:
        static constexpr size_t SSO_MAX_LEN = 12;
    
    private:
    bool is_short() const {
        return rep.short_rep.len <= SSO_MAX_LEN;
    }

    uint32_t get_prefix(const char* data, size_t len) const {
        uint32_t p = 0;
        for (size_t i = 0; i < std::min((size_t)4, len); ++i) {
            p |= (uint8_t)data[i] << (i * 8);
        }
        return p;
    }

public:
    GermanString16B() {
        rep.short_rep.len = 0;
        rep.short_rep.content[0] = '\0';
    }

    GermanString16B(const char* data) {
        if (!data) {
            new (this) GermanString16B();
            return;
        }

        size_t len = std::strlen(data);

        if (len <= SSO_MAX_LEN) {
            rep.short_rep.len = static_cast<uint8_t>(len);
            std::strncpy(rep.short_rep.content, data, 15);
            rep.short_rep.content[15] = '\0'; 
        } else {
            rep.long_rep.len = static_cast<uint32_t>(len);
            rep.long_rep.prefix = get_prefix(data, len);

            char* payload = new char[len + 1];
            std::memcpy(payload, data, len + 1);
            rep.long_rep.data_ptr = payload;
        }
    }

    ~GermanString16B() {
        if (!is_short()) {
            delete[] rep.long_rep.data_ptr;
        }
    }

    GermanString16B(const GermanString16B& other) {
        if (other.is_short()) {
            rep.short_rep = other.rep.short_rep;
        } else {
            size_t len = other.rep.long_rep.len;
            rep.long_rep.len = other.rep.long_rep.len;
            rep.long_rep.prefix = other.rep.long_rep.prefix;

            char* payload = new char[len + 1];
            std::memcpy(payload, other.rep.long_rep.data_ptr, len + 1);
            rep.long_rep.data_ptr = payload;
        }
    }

    GermanString16B& operator=(const GermanString16B& other) {
        if (this != &other) {
            if (!is_short()) {
                delete[] rep.long_rep.data_ptr;
            }
            if (other.is_short()) {
                rep.short_rep = other.rep.short_rep;
            } else {
                size_t len = other.rep.long_rep.len;
                rep.long_rep.len = other.rep.long_rep.len;
                rep.long_rep.prefix = other.rep.long_rep.prefix;

                char* payload = new char[len + 1];
                std::memcpy(payload, other.rep.long_rep.data_ptr, len + 1);
                rep.long_rep.data_ptr = payload;
            }
        }
        return *this;
    }

    const char* data() const {
        if (is_short()) {
            return rep.short_rep.content;
        } else {
            return rep.long_rep.data_ptr;
        }
    }

    size_t size() const {
        if (is_short()) {
            return rep.short_rep.len;
        } else {
            return rep.long_rep.len;
        }
    }

    
    bool prefix_aware_equals(const GermanString16B& other) const {
        if (size() != other.size()) {
            return false;
        }

        if (!is_short() && !other.is_short()) {
            if (rep.long_rep.prefix != other.rep.long_rep.prefix) {
                return false; 
            }
        }
        return std::memcmp(data(), other.data(), size()) == 0;
    }

    void print_state() const {
        std::cout << "Data: \"" << data() << "\", Size: " << size() << " bytes." << std::endl;
        std::cout << "Storage Class: " << (is_short() ? "SHORT (SSO)" : "LONG (Heap Allocated)") << std::endl;

        if (!is_short()) {
            std::cout << "  Prefix (Decimal): " << rep.long_rep.prefix << std::endl;
            std::cout << "  Data Pointer: " << (void*)rep.long_rep.data_ptr << std::endl;
        }
        std::cout << "---" << std::endl;
    }
};

int main() {
    std::cout << "--- German String (16-Byte) Demonstration ---" << std::endl;
    std::cout << "Size of GermanString16B class: " << sizeof(GermanString16B) << " bytes" << std::endl;
    std::cout << "Max SSO Length: " << GermanString16B::SSO_MAX_LEN << " chars" << std::endl;
    std::cout << "================================================" << std::endl;

    GermanString16B sso_str_1("USA");
    GermanString16B sso_str_2("DEU");
    std::cout << "Short String 1: " << sso_str_1.data() << std::endl;
    std::cout << "Short String 2: " << sso_str_2.data() << std::endl;
    std::cout << "Comparison (USA == DEU): " << (sso_str_1.prefix_aware_equals(sso_str_2) ? "EQUAL" : "NOT EQUAL") << std::endl;
    std::cout << "---" << std::endl;

    GermanString16B long_str_A("Goethe, the famous German writer.");
    GermanString16B long_str_B("Goethe's poem, 'Erlkönig'.");
    GermanString16B long_str_C("Schiller's classic plays.");

    long_str_A.print_state();
    long_str_C.print_state();
    
    std::cout << "Comparison (A vs B) - Same Prefix: " 
              << (long_str_A.prefix_aware_equals(long_str_B) ? "EQUAL" : "NOT EQUAL") << " (Requires full comparison)" << std::endl;

    std::cout << "Comparison (A vs C) - Different Prefix: " 
              << (long_str_A.prefix_aware_equals(long_str_C) ? "EQUAL" : "NOT EQUAL") << " (Fast rejection using prefix)" << std::endl;

    std::cout << "================================================" << std::endl;
    std::cout << "Demonstration complete. Destructors will clean up long strings." << std::endl;
}

    