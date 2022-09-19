using namespace js;

any w(js::number y, js::number x, js::number N)
{
    auto c = (N - 1) / 2;
    return (x - c) * (x - c) + (y - c) * (y - c) + 1;
};


any deepCopyArray(any base)
{
    if (!Array->isArray(base)) return base;
    auto result = array<any>();
    for (auto& sub : base)
    {
        result->push(deepCopyArray(sub));
    }
    return result;
};


std::tuple<boolean, any> is_valid(js::number y, js::number x, js::number dir, array<array<js::number>> grid, array<array<array<boolean>>> used)
{
    console->assert(!const_(const_(grid)[y])[x]);
    auto dir1 = dir;
    auto dir2 = (dir + 2) % dirLen;
    auto [ny11, nx11, len1] = getNext(y, x, grid, used, dir1);
    auto [ny12, nx12, len2] = getNext(y, x, grid, used, dir2);
    if (OR((ny11 == -1), (ny12 == -1))) {
        return std::tuple<boolean, undefined_t>{ false, undefined };
    }
    auto [ny21, nx21] = getNext(ny11, nx11, grid, used, dir2);
    auto [ny22, nx22] = getNext(ny12, nx12, grid, used, dir1);
    if (AND((AND((AND((AND((ny21 != -1), (ny22 != -1))), (ny21 == ny22))), (nx21 == nx22))), (const_(const_(grid)[ny21])[nx21]))) {
        return std::tuple<boolean, std::shared_ptr<Rect>>{ true, std::make_shared<Rect>(y, x, ny11, nx11, ny21, nx21, ny12, nx12) };
    }
    return std::tuple<boolean, undefined_t>{ false, undefined };
};


void applyRect(array<array<array<boolean>>> used, std::shared_ptr<Rect> rect)
{
    console->log(STR("applyRect"));
    for (auto i = 0; i < 4; i++)
    {
        auto x = const_(rect->YXs)[i]->x;
        auto y = const_(rect->YXs)[i]->y;
        auto tx = const_(rect->YXs)[(i + 1) % 4]->x;
        auto ty = const_(rect->YXs)[(i + 1) % 4]->y;
        auto dx = Math->sign(tx - x);
        auto dy = Math->sign(ty - y);
        auto dir = 0;
        for (; dir < 8; dir++)
        {
            if (AND((dx == const_(DX)[dir]), (dy == const_(DY)[dir]))) {
                break;
            }
        }
        while (OR((not_equals(x, tx)), (not_equals(y, ty))))
        {
            const_(const_(used)[y])[x][dir] = true;
            x += const_(DX)[dir];
            y += const_(DY)[dir];
            const_(const_(used)[y])[x][std::bit_xor()(dir, 4)] = true;
        }
    }
};


void removeRect(array<array<array<boolean>>> used, std::shared_ptr<Rect> rect)
{
    console->log(STR("removeRect"));
    for (auto i = 0; i < 4; i++)
    {
        auto x = const_(rect->YXs)[i]->x;
        auto y = const_(rect->YXs)[i]->y;
        auto tx = const_(rect->YXs)[(i + 1) % 4]->x;
        auto ty = const_(rect->YXs)[(i + 1) % 4]->y;
        auto dx = Math->sign(tx - x);
        auto dy = Math->sign(ty - y);
        auto dir = 0;
        for (; dir < 8; dir++)
        {
            if (AND((dx == const_(DX)[dir]), (dy == const_(DY)[dir]))) {
                break;
            }
        }
        while (OR((not_equals(x, tx)), (not_equals(y, ty))))
        {
            const_(const_(used)[y])[x][dir] = false;
            x += const_(DX)[dir];
            y += const_(DY)[dir];
            const_(const_(used)[y])[x][std::bit_xor()(dir, 4)] = false;
        }
    }
};


void printAns(array<std::shared_ptr<Rect>> ans)
{
    shared ret = string_empty;
    ret += string_empty + ans->get_length() + STR("\
");
    ans->forEach([=](auto rect) mutable
    {
        ret += rect->toOutput() + STR("\
");
    }
    );
    console->log(ret);
};


std::tuple<js::number, js::number, js::number> getNext(js::number y, js::number x, array<array<js::number>> grid, array<array<array<boolean>>> used, js::number dir)
{
    if (OR((equals(y, -1)), (equals(x, -1)))) {
        return std::tuple<js::number, js::number, js::number>{ -1, -1, -1 };
    }
    auto N = grid->get_length();
    auto len = 0;
    while (AND((AND((AND((0 < x), (x < N - 1))), (0 < y))), (y < N - 1)))
    {
        if (const_(const_(const_(used)[y])[x])[dir]) {
            return std::tuple<js::number, js::number, js::number>{ -1, -1, -1 };
        }
        y += const_(DY)[dir];
        x += const_(DX)[dir];
        len++;
        if (const_(const_(grid)[y])[x]) {
            return std::tuple<js::number, js::number, js::number>{ y, x, len };
        }
    }
    return std::tuple<js::number, js::number, js::number>{ -1, -1, -1 };
};


std::tuple<js::number, js::number> getNextWithLen(js::number y, js::number x, array<array<js::number>> grid, array<array<array<boolean>>> used, js::number dir, js::number len)
{
    if (OR((equals(y, -1)), (equals(x, -1)))) {
        return std::tuple<js::number, js::number>{ -1, -1 };
    }
    auto N = grid->get_length();
    auto cnt = 0;
    while (AND((AND((AND((0 < x), (x < N - 1))), (0 < y))), (y < N - 1)))
    {
        if (const_(const_(const_(used)[y])[x])[dir]) {
            return std::tuple<js::number, js::number>{ -1, -1 };
        }
        y += const_(DY)[dir];
        x += const_(DX)[dir];
        cnt++;
        if (OR((const_(const_(grid)[y])[x]), (cnt == len))) {
            return std::tuple<js::number, js::number>{ y, x };
        }
    }
    return std::tuple<js::number, js::number>{ -1, -1 };
};


js::number dirLen = 8;
array<js::number> DX = array<js::number>{ 1, 1, 0, -1, -1, -1, 0, 1 };
array<js::number> DY = array<js::number>{ 0, 1, 1, 1, 0, -1, -1, -1 };

void Main(void)
{
}

MAIN
