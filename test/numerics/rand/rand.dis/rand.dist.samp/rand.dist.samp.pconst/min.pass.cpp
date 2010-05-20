//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// <random>

// template<class RealType = double>
// class piecewise_constant_distribution

// result_type min() const;

#include <random>
#include <cassert>

int main()
{
    {
        typedef std::piecewise_constant_distribution<> D;
        double b[] = {10, 14, 16, 17};
        double p[] = {25, 62.5, 12.5};
        const size_t Np = sizeof(p) / sizeof(p[0]);
        D d(b, b+Np+1, p);
        assert(d.min() == 10);
    }
}
