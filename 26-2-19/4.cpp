#include <iostream>


class IPv4{
    private:
        std::string ip;
    public:
        IPv4();
        IPv4(const IPv4& other);
        IPv4(IPv4&& other);

        IPv4& operator=(const IPv4& other);
        IPv4& operator=(IPv4&& other);

        bool operator==(IPv4& other);
        IPv4 operator+(IPv4& other);

        friend std::ostream& operator<<(std::ostream& out, const IPv4& ipv4);
};
