auto print128 = [](__int128_t x) -> void
{
    if (!x)
    {
        std::cout << 0 << '\n';
        return;
    }
    bool fg = (x < 0);
    if (fg)
        x = -x;
    std::vector<int> dig;
    while (x)
    {
        dig.push_back(x % 10);
        x /= 10;
    }
    std::reverse(dig.begin(), dig.end());
    if (fg)
        std::cout << '-';
    for (int i : dig)
        std::cout << i;
    std::cout << '\n';
};