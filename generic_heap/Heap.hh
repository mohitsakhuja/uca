/**
 * Author: Mohit Sakhuja
 * Dated: 04/09/2018
 *
 * Generic implementation of Heap.
 */

#ifndef HEAP_HH
#define HEAP_HH

#include <stdexcept>
#include <utility>
#include <vector>

using namespace std;

template <class T, class Compare = less<typename vector<T>::value_type>>
class Heap {
public:
    // Typedefs for easier to read syntax.
    typedef Compare                             comparator_type;
    typedef typename vector<T>::value_type      value_type;
    typedef typename vector<T>::reference       reference;
    typedef typename vector<T>::const_reference const_reference;
    typedef typename vector<T>::size_type       size_type;

protected:
    vector<T>       container;  /* Actual data structure */
    comparator_type comparator; /* Comparator, either provided or default */

    // Helper functions.
    static int32_t get_left_child_index(int32_t index);
    static int32_t get_right_child_index(int32_t index);
    static int32_t get_parent_index(int32_t index);

    bool has_left_child(int32_t index) const;
    bool has_right_child(int32_t index) const;
    bool has_parent(int32_t index) const;

    // Get the actual element.
    const_reference left_child(int32_t index) const noexcept(false);
    const_reference right_child(int32_t index) const noexcept(false);
    const_reference parent(int32_t index) const noexcept(false);

    // Bubble an element up or down until the `comparator` condition becomes
    // false.
    void bubble_up(int32_t index);
    void bubble_down(int32_t index);

public:
    // Constructors.
    Heap()  = default;
    ~Heap() = default;

    // Stated to avoid ambiguity.
    Heap(const Heap &__heap) = default;
    Heap(Heap &&__heap)      = default;

    Heap &operator=(const Heap &__heap) = default;
    Heap &operator=(Heap &&__heap) = default;

    // Constructor when a `comparator` is provided.
    explicit Heap(const comparator_type &__comparator);

    // Operations.
    // Push an element into the heap.
    void push(const value_type &__value);
    void push(value_type &&__value);

    // Clear the previous elements, and batch insert the new elements into the
    // heap.
    void heapify(vector<T> &&__elements);
    void heapify(const vector<T> &__elements);

    // Pop the topmost element from the heap.
    void pop(void);

    bool            is_heap(void) const; /* Tests if container is heap */
    bool            empty(void) const;   /* Tells if container is empty */
    size_type       size(void) const;    /* Returns no. of elements in heap */
    const_reference top(void) const;     /* Returns topmost element */
};

/* Constructors */
template <class T, class comparator_type>
inline Heap<T, comparator_type>::Heap(const comparator_type &__comparator)
    : comparator(__comparator)
{
}

/* Push */
template <class T, class comparator_type>
inline void Heap<T, comparator_type>::push(const value_type &__value)
{
    this->container.push_back(__value);
    this->bubble_up(this->size() - 1);
}

template <class T, class comparator_type>
inline void Heap<T, comparator_type>::push(value_type &&__value)
{
    this->container.push_back(__value);
    this->bubble_up(this->size() - 1);
}

/* Heapify */
template <class T, class comparator_type>
inline void Heap<T, comparator_type>::heapify(const vector<T> &__elements)
{
    // Clear the previous elements in the container.
    this->container.clear();

    // Copy the new elements into the container.
    this->container.assign(__elements.begin(), __elements.end());

    // Bubble down the elements, starting from the last one.
    for (int32_t i = this->container.size() - 1; i >= 0; i--)
        this->bubble_down(i);
}

template <class T, class comparator_type>
inline void Heap<T, comparator_type>::heapify(vector<T> &&__elements)
{
    // Clear the previous elements in the container.
    this->container.clear();

    // Copy the new elements into the container.
    this->container.assign(__elements.begin(), __elements.end());

    // Bubble down the elements, starting from the last one.
    for (int32_t i = this->container.size() - 1; i >= 0; i--)
        this->bubble_down(i);
}

/* Pop */
template <class T, class comparator_type>
inline void Heap<T, comparator_type>::pop(void)
{
    if (!this->empty()) {
        swap(this->container.front(), this->container.back());
        this->container.pop_back();
        this->bubble_down(0);
    }
}

/* Empty */
template <class T, class comparator_type>
inline bool Heap<T, comparator_type>::empty(void) const
{
    return this->container.empty();
}

/* Size */
template <class T, class comparator_type>
inline typename Heap<T, comparator_type>::size_type
Heap<T, comparator_type>::size(void) const
{
    return this->container.size();
}

/* Top */
template <class T, class comparator_type>
inline typename Heap<T, comparator_type>::const_reference
Heap<T, comparator_type>::top(void) const
{
    return this->container.front();
}

/* Is-Heap */
template <class T, class comparator_type>
inline bool Heap<T, comparator_type>::is_heap(void) const
{
    size_type size = this->size();

    for (size_type i = 0; i < size; i++) {
        // If current node has a left child, and comparator condition holds for
        // it w.r.t. current `i`, then return false.
        if (this->has_left_child(i)
            && this->comparator(this->container.at(i), this->left_child(i)))
            return false;

        // If current node has a right child, and comparator condition holds
        // for it w.r.t. current `i`, then return false.
        if (this->has_right_child(i)
            && this->comparator(this->container.at(i), this->right_child(i)))
            return false;
    }

    return true;
}

/* Private helper functions */
/* Get index methods */
template <class T, class comparator_type>
inline int32_t Heap<T, comparator_type>::get_left_child_index(int32_t index)
{
    return 2 * index + 1;
}

template <class T, class comparator_type>
inline int32_t Heap<T, comparator_type>::get_right_child_index(int32_t index)
{
    return 2 * (index + 1);
}

template <class T, class comparator_type>
inline int32_t Heap<T, comparator_type>::get_parent_index(int32_t index)
{
    return (index - 1) / 2;
}

/* Has child/parent node methods */
template <class T, class comparator_type>
inline bool Heap<T, comparator_type>::has_left_child(int32_t index) const
{
    return get_left_child_index(index) < this->size();
}

template <class T, class comparator_type>
inline bool Heap<T, comparator_type>::has_right_child(int32_t index) const
{
    return get_right_child_index(index) < this->size();
}

template <class T, class comparator_type>
inline bool Heap<T, comparator_type>::has_parent(int32_t index) const
{
    return index < (int32_t)this->size();
}

/* Get child/parent node methods */
template <class T, class comparator_type>
inline typename Heap<T, comparator_type>::const_reference
Heap<T, comparator_type>::left_child(int32_t index) const noexcept(false)
{
    if (!this->has_left_child(index))
        throw out_of_range("Left child does not exist");

    return this->container.at(get_left_child_index(index));
}

template <class T, class comparator_type>
inline typename Heap<T, comparator_type>::const_reference
Heap<T, comparator_type>::right_child(int32_t index) const noexcept(false)
{
    if (!this->has_right_child(index))
        throw out_of_range("Right child does not exist");

    return this->container.at(get_right_child_index(index));
}

template <class T, class comparator_type>
inline typename Heap<T, comparator_type>::const_reference
Heap<T, comparator_type>::parent(int32_t index) const noexcept(false)
{
    if (!this->has_parent(index))
        throw out_of_range("Parent does not exist");

    return this->container.at(get_parent_index(index));
}

/* Bubble-up */
template <class T, class comparator_type>
inline void Heap<T, comparator_type>::bubble_up(int32_t index)
{
    // While there exists a parent for the current node, and the comparator
    // condition remains true, keep bubbling up.
    while (this->has_parent(index)
        && this->comparator(this->parent(index), this->container.at(index))) {
        // Get parent index.
        int parent_index = get_parent_index(index);

        // Swap the current element with its parent index.
        swap(this->container.at(index), this->container.at(parent_index));
        index = parent_index;
    }
}

/* Bubble-down */
template <class T, class comparator_type>
inline void Heap<T, comparator_type>::bubble_down(int32_t index)
{
    // Can only bubble-down while there is a left child.
    while (this->has_left_child(index)) {

        // Get the element at which the element can be swapped with the element
        // at the current index.
        int swappable_index = get_left_child_index(index);

        // Swappable index will be the index of the right child if that is more
        // suitable according to the comparator.
        if (this->has_right_child(index)
            && this->comparator(
                   this->left_child(index), this->right_child(index)))
            swappable_index = get_right_child_index(index);

        // If comparator condition holds true for element at the swappable
        // index, perform the swap, else break.
        if (this->comparator(this->container.at(index),
                this->container.at(swappable_index))) {
            swap(this->container.at(index),
                this->container.at(swappable_index));
            index = swappable_index;
        } else
            break;
    }
}

#endif
