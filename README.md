---
title: CS 246 Assignment 6
---

<div id="header">

| **CS 246 Assignment 6**
| due 12:55pm on Thursday, April 6, 2017

</div>

[Link back to syllabus](http://cs.brynmawr.edu/cs246/syllabus.html)

[Click here to start assignment](https://classroom.github.com/group-assignment-invitations/b8d4897b0013f20d96a3dc237ae97345)

Like all assignments, you will complete this assignment via
GitHub. See [the submission instructions](../submission.html)
for how to get the starter code and how to submit this
assignment.

You may want to use `valgrind` to test your work for memory safety. (Mac users
may want to install this with `brew install valgrind`.) If you do so, it will
be helpful to suppress memory errors caused by the `check` framework. To suppress
these errors, download the [check.supp](../14/check.supp) file and pass the
`--suppressions=check.supp` argument to `valgrind`. So, if your executable is
`check_dlist`, then you would call `valgrind --suppressions=check.supp ./check_dlist`
on the command line (with `check.supp` in the same folder as `check_dlist`).

You will likely also want to write a `Makefile` as part of this assignment.

1. Write low-level functions on `dlist_node`s by implementing all the functions in
[dlist_node.h](dlist_node.h). Write your functions in a file `dlist_node.c`.

     * `new_node` (5 points)
     * `insert_after`/`insert_before` (20 points)
     * `delete_node` (20 points)
     * `nth_node`/`nth_node_prev` (10 points)
     * `free_dlist` (10 points)
     * `from_array` (10 points)
     * `to_array` (10 points)
     * `length` (5 points)

    Although your tests will not be graded, it is to your advantage to test your work.

2. Write a storage structure backed by a doubly linked list (useful as a
[deque](https://en.wikipedia.org/wiki/Double-ended_queue)) by implementing all
the functions in [dlist.h](dlist.h). You will also have to define the `struct dlist_record`.
Write your functions in a file `dlist.c`.

     * `dlist_record` (5 points)
     * `dlist_new` (5 points)
     * `dlist_size` (5 points)
     * `dlist_push`/`dlist_push_end` (10 points)
     * `dlist_pop`/`dlist_pop_end` (10 points)
     * `dlist_peek`/`dlist_peek_end` (5 points)
     * `dlist_insert` (15 points)
     * `dlist_get` (5 points)
     * `dlist_set` (10 points)
     * `dlist_remove` (15 points)
     * `dlist_free` (5 points)

    Although your tests will not be graded, it is to your advantage to test your work.

    There will also be 20 points graded for style.

3. **`words`** (optional challenge problem, worth 10 points extra credit)

    In a file `words.c`, write a function `int words(char* input, int n, char* strings[n])`
    that breaks up `input` into up to `n` words (as delimited by
    `".,'\" \n\t!?()[]{}/&"`). Elements of the output array `strings` should
    point to the individual words. Use the library function `strtok` to do your dirty work.
