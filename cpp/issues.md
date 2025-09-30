---
title: Memory issues
layout: main
category: cpp
---

The goal of this exercise is to understand what are the main issues when dealing
with _owning_ raw pointers and how tools like an _Address sanitizer_ can help
identify them.

## Exercise: memory sanitizers

The compiler can instrument the code so that at run-time a number of checks can
be performed and, in case an anomaly is detected, a diagnostic can be issued.

Here we introduce just the address sanitizer.

```shell
$ g++ -g -Wall -Wextra -o memerrors memerrors.cpp -fsanitize=address
$ ./memerrors
...
```

Note how the compiler can sometimes warn us about problems in our code.

## Exercise: memory issues

Build and run, directly and through the _address sanitizer_, the following small
programs:

* [`non_owning_pointer.cpp`]({{ site.github.repository_name }}/hands-on/cpp/non_owning_pointer.cpp).
  Uncomment the lines containing calls to `free` or `delete` and see what the
  consequences are at run-time
* [`array_too_small.cpp`]({{ site.github.repository_name }}/hands-on/cpp/array_too_small.cpp)
* [`leak.cpp`]({{ site.github.repository_name }}/hands-on/cpp/leak.cpp). Comment the
  allocations and see what the consequences are at run-time
* [`double_delete.cpp`]({{ site.github.repository_name }}/hands-on/cpp/double_delete.cpp)
* [`missed_delete.cpp`]({{ site.github.repository_name }}/hands-on/cpp/missed_delete.cpp).
  Uncomment the lines about the `try`/`catch` block and position them in
  different places; see what the consequences are at run-time

Try and fix the problems.

## Exercise: fix issues with resource-managing types

Adapt `non_owning_pointer.cpp`, `array_too_small.cpp`, `leak.cpp`,
`double_delete.cpp` and `missed_delete.cpp` to use resource-managing types, such as
smart pointers, to fix the memory issues.
