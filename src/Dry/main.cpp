//
// Created by moinshaikh on 4/22/26.
//
/*
* The DRY rule
DRY is short for don’t repeat yourself. It means you should avoid code duplication and reuse it when
possible. This means you should create a function or a function template if your code repeats similar
operations a few times. Also, instead of creating several similar types, you should consider writing
a template.
Let’s look at an example where two functions implement the same functionality and see how we can
eliminate the duplication using a template:
// two functions implement the same functionality to return minimal int and
double values
int minimum(const int& x, const int& y) { return x < y ? x : y; }
double minimum(const double& x, const double& y) { return x < y ? x : y; }
// one template function replaces them to remove duplicated functionality
template <typename T>
T minimum(const T& x, const T& y) {
return x < y ? x : y;
}
// the calls do not differ before and after applying the rule
cout << minimum(3, 5) << endl;
cout << minimum(3.0, 5.0) << endl;
It’s also important not to reinvent the wheel when it’s not necessary—that is, not to repeat others’ work.
Nowadays, there are dozens of well-written and mature libraries that can help you write high-quality
software faster. We’d like to specifically mention a few of them: Boost, Folly, Abseil, Qt, EASTL, and BDE.
Sometimes duplicating code can have its benefits, however. One such scenario is developing microser-
vices. Of course, it’s always a good idea to follow the DRY rule inside a single microservice, but violating
the DRY rule for code used in multiple services can actually be worth it. Whether we’re talking about
model entities or logic, it’s easier to maintain multiple services when code duplication is allowed.
 */

#include<iostream>
using namespace std;

template <typename T>
T minimum(const T &x, const T &y)
{
    return x < y ? x : y;
}

int main() {
    cout << minimum(3, 5) << endl;
    cout << minimum(3.0, 5.0) << endl;

    return 0;
}