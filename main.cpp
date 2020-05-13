#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>

using namespace std;

// Внимание!
// Вообще-то тесты так писать не принято. Потому что эта реализация на коленке (а) хрупкая и (б) много чего не умеет.
// Сейчас всё же оставим так, чтобы вы могли всё это использовать, не разбираясь с дополнительными инструментами.
// Но в реальном проекте используйте Boost.Test или gtest или ещё какой-нибудь аналог.

// Подключите свой хэдер вместо VerySimpleList.h
#include "Container.hpp"
// Вместо VerySimpleList укажите имя своего класса, который тестируем
#define IMPL Tree

// Больше ничего править не требуется, просто соберитесь и запуститесь с этим main-ом с тестами


bool test1()
{
    int size = 10;
    Container<int>* impl = new IMPL<int>();
    bool test_ok = true;

    for(int i = 0; i < size; i++) {
        impl->insert(i * i);
    }

    for(int i = 0; i < size; i++) {
        if (!impl->exists(i * i)) {
            test_ok = false;
        }
        impl->remove(i * i);
        if (impl->exists(i * i)) {
            test_ok = false;
        }
    }

    delete impl;

    cout << boolalpha << "Container<int> basic API works: " << test_ok << endl;
    return test_ok;
}

bool test2()
{
    int size = 10;
    Container<string>* impl = new IMPL<string>();
    bool test_ok = true;

    for(int i = 0; i < size; i++) {
        string s = "a";
        s[0] += i;
        impl->insert(s);
    }

    for(int i = 0; i < size; i++) {
        string s = "a";
        s[0] += i;
        if (!impl->exists(s)) {
            test_ok = false;
        }
        impl->remove(s);
        if (impl->exists(s)) {
            test_ok = false;
        }
    }

    delete impl;

    cout << boolalpha << "Container<string> basic API works: " << test_ok << endl;
    return test_ok;
}

bool test5()
{
    bool test_ok = true;

    int size = 10;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }

    cout << boolalpha << "Looking for non-existing element works: " << (!impl.exists(42)) << endl;
    return test_ok;
}

bool test6()
{
    bool test_ok = true;

    int size = 10;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
    }
    impl.remove(42);

    cout << boolalpha << "Calling remove() for non-existing element does not die: " << (test_ok) << endl;
    return test_ok;
}

bool test7()
{
    bool test_ok = true;

    IMPL<int> impl;
    impl.exists(42);
    impl.remove(42);

    //vector<int> from_impl;
    //for(const auto& el: impl)
    //    from_impl.push_back(el);

    cout << boolalpha << "Empty container does not die: " << (test_ok) << endl;
    return test_ok;
}

bool test8()
{
    bool test_ok = true;

    int size = 10;
    vector<int> reference;
    vector<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
        reference.push_back(i);
    }

    int to_delete = int(size / 2);
    auto position = find(reference.begin(), reference.end(), to_delete);
    reference.erase(position);
    impl.remove(to_delete);

    //for(const auto& el: impl)
    //    from_impl.push_back(el);
    //
    //sort(reference.begin(), reference.end());
    //sort(from_impl.begin(), from_impl.end());

    for(int i = 0; i < size; i++) {
        test_ok = test_ok && (i != to_delete ? impl.exists(i) : !impl.exists(i));
    }

    cout << boolalpha << "Elements are still reachable after remove(): " << (test_ok) << endl;
    return test_ok;
}

bool test9()
{
    bool test_ok = true;

    int size = 10;
    vector<int> reference;
    vector<int> from_impl;

    IMPL<int> impl;
    for(int i = 0; i < size; i++) {
        impl.insert(i);
        impl.insert(i);
        impl.insert(i);
        reference.push_back(i);
        reference.push_back(i);
        reference.push_back(i);
    }

    //for(const auto& el: impl)
    //    from_impl.push_back(el);
    //
    //sort(reference.begin(), reference.end());
    //sort(from_impl.begin(), from_impl.end());

    cout << boolalpha << "Duplicate values are possible: " << (test_ok) << endl;
    return test_ok;
}

bool test10()
{
    bool test_ok = true;

    IMPL<int> impl1;
    impl1.insert(42);
    impl1.insert(0);
    impl1.remove(42);

    IMPL<int> impl2;
    impl2.insert(0);
    impl2.insert(42);
    impl2.remove(42);

    test_ok = (impl1.exists(0) && impl2.exists(0));

    cout << boolalpha << "Removing head element probably works: " << (test_ok) << endl;
    return test_ok;
}

int main()
{
    vector<function<bool(void)>> tests = {test1, test2, test5, test6, test7, test8, test9, test10};

    bool verdict = true;

    unsigned int count = 1;
    for(auto test : tests) {
        cout << count << ". ";
        verdict = verdict && test();
        count++;
    }

    cout << "=================================" << endl;
    cout << "Run " << (count - 1) << " tests. Verdict: " << (verdict ? "PASSED" : "FAILED") << endl;

    return 0;
}
