
# Hash Table Implementations

## Overview

Hash Table Implementations is a collection of custom, template-based hash tables developed from scratch in C++. The project explores three collision-resolution strategies: linear probing, double hashing, and separate chaining using self-balancing AVL Trees.

Each implementation provides operations for inserting, searching, updating, and removing key-associated records.

---

## Key Features

- **Multiple Collision-Resolution Strategies:** Implements linear probing, double hashing, and AVL-tree-based separate chaining.
- **Template-Based Design:** Supports custom record types with integer keys.
- **Collision Handling:** Resolves hash collisions through probing sequences or AVL Tree buckets.
- **AVL Tree Chaining:** Uses self-balancing binary search trees instead of linked lists to organize colliding records.
- **Record Management:** Supports insertion, searching, updating, and deletion.
- **Collision Tracking:** Tracks collisions in the open-addressing implementations.
- **Deletion Markers:** Distinguishes previously occupied slots from never-used positions.
- **Configurable Table Capacity:** Uses a shared constant to define hash table capacity.
- **GoogleTest Integration:** Includes testing scenarios for hash table operations and collision handling.

---

## Hash Table Implementations

### 1. Linear Probing (`OpenHash<T>`)

The `OpenHash<T>` class implements an open-addressing hash table using linear probing.

The hash function determines the initial table position:

```text
hash(key) = key % CAPACITY
```

When multiple records map to the same index, linear probing searches consecutive positions until an available slot is found.

For example, with a table capacity of 11:

| Key | Initial Index | Actual Index |
|-----|---------------|--------------|
| 15 | 4 | 4 |
| 26 | 4 | 5 |
| 37 | 4 | 6 |

All three keys initially hash to index 4. Linear probing resolves the collisions by inserting subsequent records into the next available positions.

The implementation includes:

- Sequential probing with wraparound.
- Collision counting.
- Updating existing records.
- Searching and deletion by key.
- Tombstone markers for deleted entries.

### 2. Double Hashing (`DoubleHash<T>`)

The `DoubleHash<T>` class implements open addressing with a secondary hash function used to determine the insertion probing step.

**Primary Hash Function**

```text
h1(key) = key % CAPACITY
```

**Secondary Hash Function**

```text
h2(key) = 1 + (key % (CAPACITY - 2))
```

The intended probing sequence is:

```text
index = (h1(key) + i * h2(key)) % CAPACITY
```

where `i` represents the number of probing steps.

Unlike linear probing, which examines consecutive positions, double hashing uses a key-dependent step size to distribute collisions across the table.

The implementation includes:

- Two hash functions.
- Key-dependent insertion probing.
- Collision tracking.
- Record insertion and updating.
- Searching and deletion interfaces.
- Tombstone markers for deleted records.

### 3. AVL-Tree-Based Separate Chaining (`ChainedHash<T>`)

The `ChainedHash<T>` class implements separate chaining using AVL Trees.

Instead of storing colliding records in linked lists, each hash table bucket contains an AVL Tree:

```cpp
AVL<T> _data[TABLE_SIZE];
```

Records are assigned to buckets using:

```text
hash(key) = key % TABLE_SIZE
```

If multiple records produce the same hash index, they are stored within the same AVL Tree.

**Example**

With a table capacity of 11, keys 15, 26, and 37 all hash to bucket 4:

```text
Hash Table
    |
    +-- [0] Empty
    +-- [1] Empty
    +-- [2] Empty
    +-- [3] Empty
    +-- [4] AVL Tree
    |       26
    |      /  \
    |    15    37
    +-- [5] Empty
    +-- ...
```

AVL Trees maintain balance through rotations, reducing the risk of excessively deep search paths within individual buckets.

**Key Implementation Details**

- Each bucket contains an AVL Tree.
- Records are ordered by their keys.
- Existing records can be updated without creating duplicate keys.
- Searching and deletion operate within the corresponding tree bucket.
- AVL rotations are used to maintain tree balance.

---

## Supported Operations

| Operation | Function | Description |
|-----------|----------|-------------|
| Insert | `insert()` | Inserts a record or updates an existing entry |
| Remove | `remove()` | Removes a record by key |
| Search | `find()` | Retrieves a matching record |
| Check Existence | `is_present()` | Determines whether a key exists |
| Size | `size()` | Returns the number of stored records |
| Capacity | `capacity()` | Returns the configured table capacity |
| Collision Count | `collisions()` | Returns collision counts for open-addressing tables |
| Print | `operator<<` | Displays stored records |

---

## Record Structure

The project includes a custom `record` structure containing an integer key and an associated numerical value.

```cpp
struct record {
    int _key;
    double _value;
};
```

Comparison operators compare records by their keys rather than their stored values.

This allows the data structures to locate and organize records independently of their associated data.

---

## Core Components

| File | Responsibility |
|------|----------------|
| `open_hash.h` | Implements linear probing and open-addressing operations |
| `double_hash.h` | Implements double-hashing insertion and collision tracking |
| `chained_hash.h` | Implements separate chaining using AVL Trees |
| `record.h` | Defines records and key-based comparison operators |
| `constants.h` | Defines the shared hash table capacity |
| `avl.h` | Implements the AVL Tree interface used for chaining |
| `avl_functions.h` | Implements AVL rotations, insertion, deletion, and searching |
| `tree_node.h` | Defines AVL Tree nodes and height tracking |
| `basic_test.cpp` | Contains GoogleTest hashing scenarios |
| `testB.cpp` | Provides additional insertion, searching, deletion, and debugging tests |

---

## Time Complexity

The following are conventional expected or target complexities for correctly implemented hash tables.

| Operation | Linear Probing | Double Hashing | AVL Chaining |
|-----------|----------------|----------------|--------------|
| Insert | O(1) expected | O(1) expected | O(log k) within a bucket |
| Search | O(1) expected | O(1) expected | O(log k) within a bucket |
| Delete | O(1) expected | O(1) expected | O(log k) within a bucket |
| Worst-Case Search | O(n) | O(n) | O(log k) with valid AVL balancing |

Here, `n` represents the number of stored records and `k` represents the number of records within a selected AVL Tree bucket.

Open-addressing performance depends on load factor, probing behavior, and collision distribution. These are theoretical algorithmic bounds, not measured benchmarks.

---

## Testing

The project includes test programs using **GoogleTest**, with scenarios covering:

- Record insertion and replacement.
- Searching for existing and nonexistent keys.
- Removing records.
- Randomized record insertion.
- Collision tracking.
- Hash table occupancy and record counts.
- AVL-tree-based separate chaining.
- Console-based visualization and debugging.

The testing code combines GoogleTest test cases with manual verification and diagnostic output.

---

## Project Information

**Language:** C++  
**Data Structures:** Hash Tables, AVL Trees  
**Collision Resolution:** Linear Probing, Double Hashing, AVL-Tree-Based Chaining  
**Testing:** GoogleTest  
**Core Concepts:** Hash Functions, Collision Resolution, Open Addressing, Balanced Search Trees, Templates, and Data Structure Design

**Developer:** Queency Tan
