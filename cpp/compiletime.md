---
title: Compile-time computation
layout: main
section: cpp
---

The goal of these exercises is to get some feeling about the possibilities
offered by the C++ language to perform computations at compile-time.

## Exercise 1
Implement a template function `make_array` that takes a parameter pack of arithmetic
types (with the same type) and returns a `std::array` containing those values.
Note: this exercise can be solved in a very trivial way by unpacking the pack in the
array's constructor. For didactic purposes, don't do that.

## Exercise 2

Take the `pi` function in [`pi_time.cpp`]({% include hands_on_base.md
%}/basic/pi_time.cpp) and make it `constexpr`

Look at the assembly (the easiest is to copy&paste the code into [Compiler
Explorer](https://godbolt.org/)) and verify that there is no computation
performed at runtime.

## Exercise 3

Implement a `constexpr` function that checks if a number is prime.

Like before, look at the assembly and verify that there is no computation
performed at runtime for a value known _statically_ (i.e. known at compile
time): the value can be either a literal or the result of another `constexpr`
computation.

Check that it's possible to call the function with a value not known statically,
e.g. one that is asked on the standard input.

## Exercise 4

Take [`containers_assoc.cpp`]({% include hands_on_base.md %}/{{ page.section
}}/containers_assoc.cpp) and extend it to cover also the use of the `std::set`
and `std::unordered_set` associative containers. To fill the associative
containers you can simply insert all the numbers from 0 to N, without random
generation and without advancing.

In order to dispatch to the correct implementation you can use the
`is_associative` trait already included in that file, using it either as a tag
or in a _constexpr-if_.

## Exercise 5

Construct a compile-time table corresponding to a [Pascal’s
Triangle](https://en.wikipedia.org/wiki/Pascal%27s_triangle) of N rows, where N
is a compile-time constant.

Look at the assembly and verify that there is no computation performed at
runtime for a statically-known value of a certain position, but that it's also
possible to access the value for a position obtained at runtime, e.g. from
standard input.
