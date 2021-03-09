#include <iostream>
#include <tuple>
template<typename E>
constexpr typename std::underlying_type<E>::type toUType(E enumerator) noexcept
{
    return static_cast<typename std::underlying_type<E>::type>(enumerator);
}

template<typename E> // C++14
constexpr auto toUType_t(E enumerator) noexcept
{
    return static_cast<std::underlying_type_t<E>>(enumerator);
}

int main() {
    // enum Color { black, white, red };
    // auto white = false; Error white already declared

    enum class Color { black, white, red };
    auto white = false;
    // Color c = white; Error

    Color c = Color::white;

    using UserInfo = // type alias; see Item 9
        std::tuple<std::string, // name
                   std::string, // email
                   std::size_t>; // reputation

    UserInfo uInfo { "Boris", "Boris@protonmail.ch", 0 };
    auto val = std::get<1>(uInfo);

    std::cout << val << std::endl;

    enum UserInfoFields { uiName, uiEmail, uiReputation };

    val = std::get<uiEmail>(uInfo);
    std::cout << val << std::endl;

    enum class SUserInfoFields { sUiName, sUiEmail, sUiReputation };
    // val = std::get<SUserInfoFields::sUiEmail>(uInfo); Error cast to size_t
    // std::cout << val << std::endl;


    val = std::get<static_cast<std::size_t>(SUserInfoFields::sUiEmail)>(uInfo);
    std::cout << val << std::endl;

    val = std::get<toUType_t(SUserInfoFields::sUiEmail)>(uInfo);
    std::cout << val << std::endl;
}