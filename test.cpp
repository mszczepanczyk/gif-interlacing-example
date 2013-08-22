// g++ test.cpp -o test
#include <cstdio>
#include <set>

int encode_line_number (int line_number, int height) 
{
    if ((line_number + 1) % 2 == 0) // 4th tile 1/2 sized
        return (height + line_number) / 2;
    if ((line_number + 2) % 4 == 0) // 3rd tile 1/4 sized
        return (height + line_number + 1) / 4;
    if ((line_number + 4) % 8 == 0) // 2nd tile 1/8 sized
        return (height + line_number + 3) / 8;

    // line_number % 8 == 0  (1st tile 1/8 sized)
    return line_number / 8;
}

int decode_line_number (int line_number, int height) 
{
    if (1 < height && (height + 1) / 2 <= line_number) // 4th tile 1/2 sized
        return 2 * (line_number - (height + 1) / 2) + 1;
    if (2 < height && (height + 3) / 4 <= line_number) // 3rd tile 1/4 sized
        return 4 * (line_number - (height + 3) / 4) + 2;
    if (4 < height && (height + 7) / 8 <= line_number) // 2nd tile 1/8 sized
        return 8 * (line_number - (height + 7) / 8) + 4;

    // 1st tile 1/8 sized
    return line_number * 8;
}

bool test (int height)
{
    bool ok = true;
    std::set<int> encoded, decoded;
    for (int l = 0; l < height; l++) {
        int d = decode_line_number (l, height);
        ok &= 0 <= d && d < height;
        decoded.insert (d);

        int e = encode_line_number (l, height);
        ok &= 0 <= e && e < height;
        encoded.insert (e);

        ok &= (l == encode_line_number(decode_line_number(l, height), height));
        ok &= (l == decode_line_number(encode_line_number(l, height), height));
    }

    ok &= decoded.size() == height;
    ok &= encoded.size() == height;

    return ok;
}

int main()
{
    for (int h = 0; h <= 100; h++) {
        int ok = test (h);
        printf("%3d: %s\n", h, ok ? "OK" : "WRONG!");
        if (!ok) break;
    }

    return 0;
}
